#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ cache_count; struct TYPE_9__* next; } ;
typedef  TYPE_1__ zbar_symbol_t ;
struct TYPE_10__ {TYPE_1__* tail; int /*<<< orphan*/  nsyms; TYPE_1__* head; } ;
typedef  TYPE_2__ zbar_symbol_set_t ;
struct TYPE_11__ {TYPE_2__* syms; } ;
typedef  TYPE_3__ zbar_image_scanner_t ;

/* Variables and functions */
 int /*<<< orphan*/  _zbar_symbol_refcnt (TYPE_1__*,int) ; 
 int /*<<< orphan*/  cache_sym (TYPE_3__*,TYPE_1__*) ; 

void _zbar_image_scanner_add_sym(zbar_image_scanner_t *iscn,
                                 zbar_symbol_t *sym)
{
    zbar_symbol_set_t *syms;
    cache_sym(iscn, sym);

    syms = iscn->syms;
    if(sym->cache_count || !syms->tail) {
        sym->next = syms->head;
        syms->head = sym;
    }
    else {
        sym->next = syms->tail->next;
        syms->tail->next = sym;
    }

    if(!sym->cache_count)
        syms->nsyms++;
    else if(!syms->tail)
        syms->tail = sym;

    _zbar_symbol_refcnt(sym, 1);
}