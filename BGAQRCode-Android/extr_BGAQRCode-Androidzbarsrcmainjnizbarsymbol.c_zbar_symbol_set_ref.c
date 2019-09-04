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
struct TYPE_4__ {int /*<<< orphan*/  refcnt; } ;
typedef  TYPE_1__ zbar_symbol_set_t ;

/* Variables and functions */
 int /*<<< orphan*/  _zbar_refcnt (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  _zbar_symbol_set_free (TYPE_1__*) ; 

void zbar_symbol_set_ref (const zbar_symbol_set_t *syms,
                          int delta)
{
    zbar_symbol_set_t *ncsyms = (zbar_symbol_set_t*)syms;
    if(!_zbar_refcnt(&ncsyms->refcnt, delta) && delta <= 0)
        _zbar_symbol_set_free(ncsyms);
}