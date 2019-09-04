#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ zbar_symbol_type_t ;
struct TYPE_6__ {unsigned int* w; int idx; int /*<<< orphan*/  (* handler ) (TYPE_1__*) ;scalar_t__ lock; scalar_t__ type; int /*<<< orphan*/  s6; } ;
typedef  TYPE_1__ zbar_decoder_t ;

/* Variables and functions */
 int DECODE_WINDOW ; 
 scalar_t__ ZBAR_NONE ; 
 scalar_t__ ZBAR_PARTIAL ; 
 scalar_t__ ZBAR_QRCODE ; 
 int /*<<< orphan*/  dbprintf (int,char*,int,unsigned int,unsigned int) ; 
 scalar_t__ get_width (TYPE_1__*,int) ; 
 int /*<<< orphan*/  release_lock (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

zbar_symbol_type_t zbar_decode_width (zbar_decoder_t *dcode,
                                      unsigned w)
{
    zbar_symbol_type_t tmp, sym = ZBAR_NONE;

    dcode->w[dcode->idx & (DECODE_WINDOW - 1)] = w;
    dbprintf(1, "    decode[%x]: w=%d (%g)\n", dcode->idx, w, (w / 32.));

    /* update shared character width */
    dcode->s6 -= get_width(dcode, 7);
    dcode->s6 += get_width(dcode, 1);

    /* each decoder processes width stream in parallel */
#ifdef ENABLE_QRCODE
    if(TEST_CFG(dcode->qrf.config, ZBAR_CFG_ENABLE) &&
       (tmp = _zbar_find_qr(dcode)) > ZBAR_PARTIAL)
        sym = tmp;
#endif
#ifdef ENABLE_EAN
    if((dcode->ean.enable) &&
       (tmp = _zbar_decode_ean(dcode)))
        sym = tmp;
#endif
#ifdef ENABLE_CODE39
    if(TEST_CFG(dcode->code39.config, ZBAR_CFG_ENABLE) &&
       (tmp = _zbar_decode_code39(dcode)) > ZBAR_PARTIAL)
        sym = tmp;
#endif
#ifdef ENABLE_CODE93
    if(TEST_CFG(dcode->code93.config, ZBAR_CFG_ENABLE) &&
       (tmp = _zbar_decode_code93(dcode)) > ZBAR_PARTIAL)
        sym = tmp;
#endif
#ifdef ENABLE_CODE128
    if(TEST_CFG(dcode->code128.config, ZBAR_CFG_ENABLE) &&
       (tmp = _zbar_decode_code128(dcode)) > ZBAR_PARTIAL)
        sym = tmp;
#endif
#ifdef ENABLE_DATABAR
    if(TEST_CFG(dcode->databar.config | dcode->databar.config_exp,
                ZBAR_CFG_ENABLE) &&
       (tmp = _zbar_decode_databar(dcode)) > ZBAR_PARTIAL)
        sym = tmp;
#endif
#ifdef ENABLE_CODABAR
    if(TEST_CFG(dcode->codabar.config, ZBAR_CFG_ENABLE) &&
       (tmp = _zbar_decode_codabar(dcode)) > ZBAR_PARTIAL)
        sym = tmp;
#endif
#ifdef ENABLE_I25
    if(TEST_CFG(dcode->i25.config, ZBAR_CFG_ENABLE) &&
       (tmp = _zbar_decode_i25(dcode)) > ZBAR_PARTIAL)
        sym = tmp;
#endif
#ifdef ENABLE_PDF417
    if(TEST_CFG(dcode->pdf417.config, ZBAR_CFG_ENABLE) &&
       (tmp = _zbar_decode_pdf417(dcode)) > ZBAR_PARTIAL)
        sym = tmp;
#endif

    dcode->idx++;
    dcode->type = sym;
    if(sym) {
        if(dcode->lock && sym > ZBAR_PARTIAL && sym != ZBAR_QRCODE)
            release_lock(dcode, sym);
        if(dcode->handler)
            dcode->handler(dcode);
    }
    return(sym);
}