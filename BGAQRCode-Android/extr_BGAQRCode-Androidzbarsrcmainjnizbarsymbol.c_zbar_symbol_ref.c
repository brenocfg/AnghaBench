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
typedef  int /*<<< orphan*/  zbar_symbol_t ;

/* Variables and functions */
 int /*<<< orphan*/  _zbar_symbol_refcnt (int /*<<< orphan*/ *,int) ; 

void zbar_symbol_ref (const zbar_symbol_t *sym,
                      int refs)
{
    zbar_symbol_t *ncsym = (zbar_symbol_t*)sym;
    _zbar_symbol_refcnt(ncsym, refs);
}