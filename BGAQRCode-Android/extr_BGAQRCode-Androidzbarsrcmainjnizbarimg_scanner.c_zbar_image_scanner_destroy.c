#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {struct TYPE_11__* next; } ;
typedef  TYPE_2__ zbar_symbol_t ;
struct TYPE_12__ {TYPE_1__* recycle; int /*<<< orphan*/ * dcode; int /*<<< orphan*/ * scn; TYPE_4__* syms; } ;
typedef  TYPE_3__ zbar_image_scanner_t ;
struct TYPE_13__ {scalar_t__ refcnt; } ;
struct TYPE_10__ {TYPE_2__* head; } ;

/* Variables and functions */
 int RECYCLE_BUCKETS ; 
 int /*<<< orphan*/  _zbar_symbol_free (TYPE_2__*) ; 
 int /*<<< orphan*/  _zbar_symbol_set_free (TYPE_4__*) ; 
 int /*<<< orphan*/  dump_stats (TYPE_3__*) ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 int /*<<< orphan*/  zbar_decoder_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zbar_scanner_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zbar_symbol_set_ref (TYPE_4__*,int) ; 

void zbar_image_scanner_destroy (zbar_image_scanner_t *iscn)
{
    int i;
    dump_stats(iscn);
    if(iscn->syms) {
        if(iscn->syms->refcnt)
            zbar_symbol_set_ref(iscn->syms, -1);
        else
            _zbar_symbol_set_free(iscn->syms);
        iscn->syms = NULL;
    }
    if(iscn->scn)
        zbar_scanner_destroy(iscn->scn);
    iscn->scn = NULL;
    if(iscn->dcode)
        zbar_decoder_destroy(iscn->dcode);
    iscn->dcode = NULL;
    for(i = 0; i < RECYCLE_BUCKETS; i++) {
        zbar_symbol_t *sym, *next;
        for(sym = iscn->recycle[i].head; sym; sym = next) {
            next = sym->next;
            _zbar_symbol_free(sym);
        }
    }
#ifdef ENABLE_QRCODE
    if(iscn->qr) {
        _zbar_qr_destroy(iscn->qr);
        iscn->qr = NULL;
    }
#endif
    free(iscn);
}