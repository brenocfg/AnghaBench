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
typedef  int u_long ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int const_strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dates_are_valid (char*,int) ; 
 int /*<<< orphan*/  kCopyrightToken ; 
 int /*<<< orphan*/  kRightsToken ; 
 char* kxld_alloc (int) ; 
 int /*<<< orphan*/  kxld_free (char*,int) ; 
 char* kxld_strstr (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 

boolean_t 
kxld_validate_copyright_string(const char *str)
{
    boolean_t result = FALSE;
    const char *copyright = NULL;
    const char *rights = NULL;
    char *date_str = NULL;
    u_long len = 0;

    copyright = kxld_strstr(str, kCopyrightToken);
    rights = kxld_strstr(str, kRightsToken);

    if (!copyright || !rights || copyright > rights) goto finish;

    str = copyright + const_strlen(kCopyrightToken);

    len = rights - str;
    date_str = kxld_alloc(len+1);
    if (!date_str) goto finish;

    strncpy(date_str, str, len);
    date_str[len] = '\0';

    if (!dates_are_valid(date_str, len)) goto finish;

    result = TRUE;
finish:
    if (date_str) kxld_free(date_str, len+1);
    return result;
}