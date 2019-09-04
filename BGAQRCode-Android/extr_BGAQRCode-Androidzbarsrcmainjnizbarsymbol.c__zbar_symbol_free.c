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
struct TYPE_4__ {struct TYPE_4__* data; scalar_t__ data_alloc; struct TYPE_4__* pts; int /*<<< orphan*/ * syms; } ;
typedef  TYPE_1__ zbar_symbol_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  zbar_symbol_set_ref (int /*<<< orphan*/ *,int) ; 

void _zbar_symbol_free (zbar_symbol_t *sym)
{
    if(sym->syms) {
        zbar_symbol_set_ref(sym->syms, -1);
        sym->syms = NULL;
    }
    if(sym->pts)
        free(sym->pts);
    if(sym->data_alloc && sym->data)
        free(sym->data);
    free(sym);
}