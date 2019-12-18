#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ cfgStatus; } ;
typedef  TYPE_1__ SGlobalConfig ;

/* Variables and functions */
 int /*<<< orphan*/  LC_CTYPE ; 
 scalar_t__ TSDB_CFG_CSTATUS_DEFAULT ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  pError (char*) ; 
 int /*<<< orphan*/  pPrint (char*,int /*<<< orphan*/ ) ; 
 char* setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 char* strrchr (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  tListLen (int /*<<< orphan*/ ) ; 
 char* taosCharsetReplace (char*) ; 
 int /*<<< orphan*/  tsCharset ; 
 TYPE_1__* tsGetConfigOption (char*) ; 
 int /*<<< orphan*/  tsLocale ; 

void taosGetSystemLocale() {  // get and set default locale
  char  sep = '.';
  char *locale = NULL;

  SGlobalConfig *cfg_locale = tsGetConfigOption("locale");
  if (cfg_locale && cfg_locale->cfgStatus < TSDB_CFG_CSTATUS_DEFAULT) {
    locale = setlocale(LC_CTYPE, "");
    if (locale == NULL) {
      pError("can't get locale from system");
    } else {
      strncpy(tsLocale, locale, tListLen(tsLocale));
      pPrint("locale not configured, set to system default:%s", tsLocale);
    }
  }

  /* if user does not specify the charset, extract it from locale */
  SGlobalConfig *cfg_charset = tsGetConfigOption("charset");
  if (cfg_charset && cfg_charset->cfgStatus < TSDB_CFG_CSTATUS_DEFAULT) {
    char *str = strrchr(tsLocale, sep);
    if (str != NULL) {
      str++;

      char *revisedCharset = taosCharsetReplace(str);
      strncpy(tsCharset, revisedCharset, tListLen(tsCharset));

      free(revisedCharset);
      pPrint("charset not configured, set to system default:%s", tsCharset);
    }
  }
}