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
struct TYPE_3__ {scalar_t__ nsyms; int /*<<< orphan*/ * tail; int /*<<< orphan*/  head; int /*<<< orphan*/  refcnt; } ;
typedef  TYPE_1__ zbar_symbol_set_t ;
typedef  int /*<<< orphan*/  zbar_image_scanner_t ;

/* Variables and functions */
 int /*<<< orphan*/  _zbar_image_scanner_recycle_syms (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ _zbar_refcnt (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline int recycle_syms (zbar_image_scanner_t *iscn,
                                zbar_symbol_set_t *syms)
{
    if(_zbar_refcnt(&syms->refcnt, -1))
        return(1);

    _zbar_image_scanner_recycle_syms(iscn, syms->head);
    syms->head = syms->tail = NULL;
    syms->nsyms = 0;
    return(0);
}