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
struct TYPE_9__ {scalar_t__ refcnt; } ;
typedef  TYPE_1__ zbar_symbol_set_t ;
struct TYPE_10__ {TYPE_1__* syms; } ;
typedef  TYPE_2__ zbar_image_t ;
struct TYPE_11__ {TYPE_1__* syms; } ;
typedef  TYPE_3__ zbar_image_scanner_t ;

/* Variables and functions */
 int /*<<< orphan*/  STAT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _zbar_symbol_set_free (TYPE_1__*) ; 
 int /*<<< orphan*/  img_syms_inuse ; 
 int /*<<< orphan*/  img_syms_recycle ; 
 int /*<<< orphan*/  iscn_syms_inuse ; 
 int /*<<< orphan*/  iscn_syms_recycle ; 
 scalar_t__ recycle_syms (TYPE_3__*,TYPE_1__*) ; 

inline void zbar_image_scanner_recycle_image (zbar_image_scanner_t *iscn,
                                              zbar_image_t *img)
{
    zbar_symbol_set_t *syms = iscn->syms;
    if(syms && syms->refcnt) {
        if(recycle_syms(iscn, syms)) {
            STAT(iscn_syms_inuse);
            iscn->syms = NULL;
        }
        else
            STAT(iscn_syms_recycle);
    }

    syms = img->syms;
    img->syms = NULL;
    if(syms && recycle_syms(iscn, syms))
        STAT(img_syms_inuse);
    else if(syms) {
        STAT(img_syms_recycle);

        /* select one set to resurrect, destroy the other */
        if(iscn->syms)
            _zbar_symbol_set_free(syms);
        else
            iscn->syms = syms;
    }
}