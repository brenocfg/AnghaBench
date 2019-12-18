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
typedef  size_t int32_t ;
struct TYPE_3__ {char* member_0; char* member_1; char* newCharset; int /*<<< orphan*/  oldCharset; } ;
typedef  TYPE_1__ CharsetPair ;

/* Variables and functions */
 scalar_t__ strcasecmp (int /*<<< orphan*/ ,char*) ; 
 char* strdup (char*) ; 
 size_t tListLen (TYPE_1__*) ; 

char *taosCharsetReplace(char *charsetstr) {
  CharsetPair charsetRep[] = {
      {"utf8", "UTF-8"}, {"936", "CP936"},
  };

  for (int32_t i = 0; i < tListLen(charsetRep); ++i) {
    if (strcasecmp(charsetRep[i].oldCharset, charsetstr) == 0) {
      return strdup(charsetRep[i].newCharset);
    }
  }

  return strdup(charsetstr);
}