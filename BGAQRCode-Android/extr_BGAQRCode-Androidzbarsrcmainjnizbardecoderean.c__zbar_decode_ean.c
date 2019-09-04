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
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ zbar_symbol_type_t ;
struct TYPE_13__ {TYPE_2__* pass; int /*<<< orphan*/  s4; } ;
struct TYPE_11__ {int idx; int /*<<< orphan*/  lock; TYPE_4__ ean; } ;
typedef  TYPE_1__ zbar_decoder_t ;
struct TYPE_12__ {scalar_t__ state; } ;
typedef  TYPE_2__ ean_pass_t ;

/* Variables and functions */
 scalar_t__ ZBAR_NONE ; 
 scalar_t__ ZBAR_PARTIAL ; 
 int /*<<< orphan*/  acquire_lock (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  dbprintf (int,char*,...) ; 
 scalar_t__ decode_pass (TYPE_1__*,TYPE_2__*) ; 
 scalar_t__ get_width (TYPE_1__*,int) ; 
 scalar_t__ integrate_partial (TYPE_4__*,TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  postprocess (TYPE_1__*,scalar_t__) ; 

zbar_symbol_type_t _zbar_decode_ean (zbar_decoder_t *dcode)
{
    /* process upto 4 separate passes */
    zbar_symbol_type_t sym = ZBAR_NONE;
    unsigned char pass_idx = dcode->idx & 3;
    unsigned char i;

    /* update latest character width */
    dcode->ean.s4 -= get_width(dcode, 4);
    dcode->ean.s4 += get_width(dcode, 0);

    for(i = 0; i < 4; i++) {
        ean_pass_t *pass = &dcode->ean.pass[i];
        if(pass->state >= 0 ||
           i == pass_idx)
        {
            zbar_symbol_type_t part;
            dbprintf(2, "      ean[%x/%x]: idx=%x st=%d s=%d",
                     i, pass_idx, dcode->idx, pass->state, dcode->ean.s4);
            part = decode_pass(dcode, pass);
            if(part) {
                /* update accumulated data from new partial decode */
                sym = integrate_partial(&dcode->ean, pass, part);
                if(sym) {
                    /* this pass valid => _reset_ all passes */
                    dbprintf(2, " sym=%x", sym);
                    dcode->ean.pass[0].state = dcode->ean.pass[1].state = -1;
                    dcode->ean.pass[2].state = dcode->ean.pass[3].state = -1;
                    if(sym > ZBAR_PARTIAL) {
                        if(!acquire_lock(dcode, sym))
                            postprocess(dcode, sym);
                        else {
                            dbprintf(1, " [locked %d]", dcode->lock);
                            sym = ZBAR_PARTIAL;
                        }
                    }
                }
            }
            dbprintf(2, "\n");
        }
    }
    return(sym);
}