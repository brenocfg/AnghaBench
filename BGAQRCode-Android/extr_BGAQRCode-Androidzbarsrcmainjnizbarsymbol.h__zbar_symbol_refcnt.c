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
typedef  TYPE_1__ zbar_symbol_t ;

/* Variables and functions */
 int /*<<< orphan*/  _zbar_refcnt (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  _zbar_symbol_free (TYPE_1__*) ; 

__attribute__((used)) static inline void _zbar_symbol_refcnt (zbar_symbol_t *sym,
                                        int delta)
{
    if(!_zbar_refcnt(&sym->refcnt, delta) && delta <= 0)
        _zbar_symbol_free(sym);
}