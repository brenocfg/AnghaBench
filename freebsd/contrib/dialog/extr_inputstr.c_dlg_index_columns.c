#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  temp ;
typedef  int /*<<< orphan*/  state ;
typedef  int /*<<< orphan*/  mbstate_t ;
typedef  char const chtype ;
typedef  int /*<<< orphan*/  cchar_t ;
struct TYPE_4__ {int* list; } ;
typedef  TYPE_1__ CACHE ;

/* Variables and functions */
 char const TAB ; 
 char UCH (char const) ; 
 int /*<<< orphan*/  cInxCols ; 
 int /*<<< orphan*/  dlg_count_wchars (char const*) ; 
 int* dlg_index_wchars (char const*) ; 
 scalar_t__ have_locale () ; 
 scalar_t__ isprint (char) ; 
 TYPE_1__* load_cache (int /*<<< orphan*/ ,char const*) ; 
 size_t mbrtowc (int /*<<< orphan*/ *,char const*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  same_cache2 (TYPE_1__*,char const*,unsigned int) ; 
 int /*<<< orphan*/  setcchar (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t strlen (char const*) ; 
 char* unctrl (char const) ; 
 scalar_t__ wcslen (int /*<<< orphan*/  const*) ; 
 int wcwidth (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * wunctrl (int /*<<< orphan*/ *) ; 

const int *
dlg_index_columns(const char *string)
{
    unsigned len = (unsigned) dlg_count_wchars(string);
    unsigned inx;
    CACHE *cache = load_cache(cInxCols, string);

    if (!same_cache2(cache, string, len)) {
	cache->list[0] = 0;
#ifdef USE_WIDE_CURSES
	if (have_locale()) {
	    size_t num_bytes = strlen(string);
	    const int *inx_wchars = dlg_index_wchars(string);
	    mbstate_t state;

	    for (inx = 0; inx < len; ++inx) {
		wchar_t temp[2];
		size_t check;
		int result;

		if (string[inx_wchars[inx]] == TAB) {
		    result = ((cache->list[inx] | 7) + 1) - cache->list[inx];
		} else {
		    memset(&state, 0, sizeof(state));
		    memset(temp, 0, sizeof(temp));
		    check = mbrtowc(temp,
				    string + inx_wchars[inx],
				    num_bytes - (size_t) inx_wchars[inx],
				    &state);
		    if ((int) check <= 0) {
			result = 1;
		    } else {
			result = wcwidth(temp[0]);
		    }
		    if (result < 0) {
			const wchar_t *printable;
			cchar_t temp2, *temp2p = &temp2;
			setcchar(temp2p, temp, 0, 0, 0);
			printable = wunctrl(temp2p);
			result = printable ? (int) wcslen(printable) : 1;
		    }
		}
		cache->list[inx + 1] = result;
		if (inx != 0)
		    cache->list[inx + 1] += cache->list[inx];
	    }
	} else
#endif /* USE_WIDE_CURSES */
	{
	    for (inx = 0; inx < len; ++inx) {
		chtype ch = UCH(string[inx]);

		if (ch == TAB)
		    cache->list[inx + 1] =
			((cache->list[inx] | 7) + 1) - cache->list[inx];
		else if (isprint(UCH(ch)))
		    cache->list[inx + 1] = 1;
		else {
		    const char *printable;
		    printable = unctrl(ch);
		    cache->list[inx + 1] = (printable
					    ? (int) strlen(printable)
					    : 1);
		}
		if (inx != 0)
		    cache->list[inx + 1] += cache->list[inx];
	    }
	}
    }
    return cache->list;
}