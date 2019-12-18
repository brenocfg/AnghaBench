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
struct TYPE_3__ {char const* pat; int rc; int /*<<< orphan*/  rx; int /*<<< orphan*/ * old_lc_ctype; int /*<<< orphan*/ * c_lc_ctype; } ;
typedef  TYPE_1__ file_regex_t ;

/* Variables and functions */
 int /*<<< orphan*/  LC_CTYPE ; 
 int /*<<< orphan*/  LC_CTYPE_MASK ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * newlocale (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int regcomp (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/ * setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * uselocale (int /*<<< orphan*/ *) ; 

int
file_regcomp(file_regex_t *rx, const char *pat, int flags)
{
#ifdef USE_C_LOCALE
	rx->c_lc_ctype = newlocale(LC_CTYPE_MASK, "C", 0);
	assert(rx->c_lc_ctype != NULL);
	rx->old_lc_ctype = uselocale(rx->c_lc_ctype);
	assert(rx->old_lc_ctype != NULL);
#else
	rx->old_lc_ctype = setlocale(LC_CTYPE, "C");
#endif
	rx->pat = pat;

	return rx->rc = regcomp(&rx->rx, pat, flags);
}