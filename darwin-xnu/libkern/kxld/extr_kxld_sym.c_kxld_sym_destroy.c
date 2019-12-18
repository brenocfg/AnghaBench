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
typedef  int /*<<< orphan*/  KXLDSym ;

/* Variables and functions */
 int /*<<< orphan*/  check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kxld_free (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kxld_sym_deinit (int /*<<< orphan*/ *) ; 

void
kxld_sym_destroy(KXLDSym *sym)
{
    check(sym);
    kxld_sym_deinit(sym);
    kxld_free(sym, sizeof(*sym));
}