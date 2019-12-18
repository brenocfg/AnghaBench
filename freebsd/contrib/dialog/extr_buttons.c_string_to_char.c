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
typedef  int wchar_t ;
typedef  int /*<<< orphan*/  state ;
typedef  int mbstate_t ;
typedef  int /*<<< orphan*/  cmp2 ;

/* Variables and functions */
 void* UCH (char const) ; 
 size_t mbrlen (char const*,size_t,int*) ; 
 size_t mbrtowc (int*,char const*,size_t,int*) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static int
string_to_char(const char **stringp)
{
    int result;
#ifdef USE_WIDE_CURSES
    const char *string = *stringp;
    size_t have = strlen(string);
    size_t check;
    size_t len;
    wchar_t cmp2[2];
    mbstate_t state;

    memset(&state, 0, sizeof(state));
    len = mbrlen(string, have, &state);
    if ((int) len > 0 && len <= have) {
	memset(&state, 0, sizeof(state));
	memset(cmp2, 0, sizeof(cmp2));
	check = mbrtowc(cmp2, string, len, &state);
	if ((int) check <= 0)
	    cmp2[0] = 0;
	*stringp += len;
    } else {
	cmp2[0] = UCH(*string);
	*stringp += 1;
    }
    result = cmp2[0];
#else
    const char *string = *stringp;
    result = UCH(*string);
    *stringp += 1;
#endif
    return result;
}