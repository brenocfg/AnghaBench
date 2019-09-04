#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* next; } ;
typedef  TYPE_1__ zbar_symbol_t ;
struct TYPE_7__ {TYPE_1__* head; } ;
typedef  TYPE_2__ zbar_symbol_set_t ;

/* Variables and functions */
 int /*<<< orphan*/  _zbar_symbol_refcnt (TYPE_1__*,int) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 

inline void _zbar_symbol_set_free (zbar_symbol_set_t *syms)
{
    zbar_symbol_t *sym, *next;
    for(sym = syms->head; sym; sym = next) {
        next = sym->next;
        sym->next = NULL;
        _zbar_symbol_refcnt(sym, -1);
    }
    syms->head = NULL;
    free(syms);
}