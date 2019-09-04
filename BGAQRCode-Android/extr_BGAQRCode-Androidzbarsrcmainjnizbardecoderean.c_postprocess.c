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
typedef  int zbar_symbol_type_t ;
struct TYPE_7__ {scalar_t__* buf; int direction; int /*<<< orphan*/  isbn10_config; } ;
struct TYPE_6__ {scalar_t__* buf; int buflen; int direction; scalar_t__ modifiers; TYPE_2__ ean; } ;
typedef  TYPE_1__ zbar_decoder_t ;
typedef  TYPE_2__ ean_decoder_t ;

/* Variables and functions */
 scalar_t__ TEST_CFG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZBAR_CFG_EMIT_CHECK ; 
 int ZBAR_EAN13 ; 
 int ZBAR_EAN5 ; 
 int ZBAR_ISBN10 ; 
 int ZBAR_ISBN13 ; 
 int ZBAR_PARTIAL ; 
 int ZBAR_UPCA ; 
 int ZBAR_UPCE ; 
 int /*<<< orphan*/  dbprintf (int,char*,int,int,char*) ; 
 int /*<<< orphan*/  ean_get_config (TYPE_2__*,int) ; 
 scalar_t__ isbn10_calc_checksum (TYPE_2__*) ; 

__attribute__((used)) static inline void postprocess (zbar_decoder_t *dcode,
                                zbar_symbol_type_t sym)
{
    ean_decoder_t *ean = &dcode->ean;
    zbar_symbol_type_t base = sym;
    int i = 0, j = 0;
    if(base > ZBAR_PARTIAL) {
        if(base == ZBAR_UPCA)
            i = 1;
        else if(base == ZBAR_UPCE) {
            i = 1;
            base--;
        }
        else if(base == ZBAR_ISBN13)
            base = ZBAR_EAN13;
        else if(base == ZBAR_ISBN10)
            i = 3;

        if(base == ZBAR_ISBN10 ||
           (base > ZBAR_EAN5 &&
            !TEST_CFG(ean_get_config(ean, sym), ZBAR_CFG_EMIT_CHECK)))
            base--;

        for(; j < base && ean->buf[i] >= 0; i++, j++)
            dcode->buf[j] = ean->buf[i] + '0';

        if(sym == ZBAR_ISBN10 && j == 9 &&
           TEST_CFG(ean->isbn10_config, ZBAR_CFG_EMIT_CHECK))
            /* recalculate ISBN-10 check digit */
            dcode->buf[j++] = isbn10_calc_checksum(ean);
    }
    dcode->buflen = j;
    dcode->buf[j] = '\0';
    dcode->direction = 1 - 2 * ean->direction;
    dcode->modifiers = 0;
    dbprintf(2, " base=%d j=%d (%s)", base, j, dcode->buf);
}