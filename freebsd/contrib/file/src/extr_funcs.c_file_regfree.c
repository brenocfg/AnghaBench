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
struct TYPE_3__ {scalar_t__ rc; int /*<<< orphan*/  old_lc_ctype; int /*<<< orphan*/  c_lc_ctype; int /*<<< orphan*/  rx; } ;
typedef  TYPE_1__ file_regex_t ;

/* Variables and functions */
 int /*<<< orphan*/  LC_CTYPE ; 
 int /*<<< orphan*/  freelocale (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uselocale (int /*<<< orphan*/ ) ; 

void
file_regfree(file_regex_t *rx)
{
	if (rx->rc == 0)
		regfree(&rx->rx);
#ifdef USE_C_LOCALE
	(void)uselocale(rx->old_lc_ctype);
	freelocale(rx->c_lc_ctype);
#else
	(void)setlocale(LC_CTYPE, rx->old_lc_ctype);
#endif
}