#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  LC_CTYPE ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  pPrint (char*,...) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 char* setlocale (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  taosValidateEncodec (char*) ; 
 char* tsCharset ; 
 char* tsLocale ; 

void tsSetLocale() {
  char msgLocale[] = "Invalid locale:%s, please set the valid locale in config file";
  char msgCharset[] = "Invalid charset:%s, please set the valid charset in config file";
  char msgCharset1[] = "failed to get charset, please set the valid charset in config file";

  char *locale = setlocale(LC_CTYPE, tsLocale);

  // default locale or user specified locale is not valid, abort launch
  if (locale == NULL) {
    printf(msgLocale, tsLocale);
    pPrint(msgLocale, tsLocale);
  }

  if (strlen(tsCharset) == 0) {
    printf("%s\n", msgCharset1);
    pPrint(msgCharset1);
    exit(-1);
  }

  if (!taosValidateEncodec(tsCharset)) {
    printf(msgCharset, tsCharset);
    pPrint(msgCharset, tsCharset);
    exit(-1);
  }
}