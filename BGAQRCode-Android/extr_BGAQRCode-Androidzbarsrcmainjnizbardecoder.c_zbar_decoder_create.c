#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  buf_alloc; int /*<<< orphan*/  buf; } ;
typedef  TYPE_1__ zbar_decoder_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_MIN ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zbar_decoder_reset (TYPE_1__*) ; 

zbar_decoder_t *zbar_decoder_create ()
{
    zbar_decoder_t *dcode = calloc(1, sizeof(zbar_decoder_t));
    dcode->buf_alloc = BUFFER_MIN;
    dcode->buf = malloc(dcode->buf_alloc);

    /* initialize default configs */
#ifdef ENABLE_EAN
    dcode->ean.enable = 1;
    dcode->ean.ean13_config = ((1 << ZBAR_CFG_ENABLE) |
                               (1 << ZBAR_CFG_EMIT_CHECK));
    dcode->ean.ean8_config = ((1 << ZBAR_CFG_ENABLE) |
                              (1 << ZBAR_CFG_EMIT_CHECK));
    dcode->ean.upca_config = 1 << ZBAR_CFG_EMIT_CHECK;
    dcode->ean.upce_config = 1 << ZBAR_CFG_EMIT_CHECK;
    dcode->ean.isbn10_config = 1 << ZBAR_CFG_EMIT_CHECK;
    dcode->ean.isbn13_config = 1 << ZBAR_CFG_EMIT_CHECK;
# ifdef FIXME_ADDON_SYNC
    dcode->ean.ean2_config = 1 << ZBAR_CFG_ENABLE;
    dcode->ean.ean5_config = 1 << ZBAR_CFG_ENABLE;
# endif
#endif
#ifdef ENABLE_I25
    dcode->i25.config = 1 << ZBAR_CFG_ENABLE;
    CFG(dcode->i25, ZBAR_CFG_MIN_LEN) = 6;
#endif
#ifdef ENABLE_DATABAR
    dcode->databar.config = ((1 << ZBAR_CFG_ENABLE) |
                             (1 << ZBAR_CFG_EMIT_CHECK));
    dcode->databar.config_exp = ((1 << ZBAR_CFG_ENABLE) |
                                 (1 << ZBAR_CFG_EMIT_CHECK));
    dcode->databar.csegs = 4;
    dcode->databar.segs = calloc(4, sizeof(*dcode->databar.segs));
#endif
#ifdef ENABLE_CODABAR
    dcode->codabar.config = 1 << ZBAR_CFG_ENABLE;
    CFG(dcode->codabar, ZBAR_CFG_MIN_LEN) = 4;
#endif
#ifdef ENABLE_CODE39
    dcode->code39.config = 1 << ZBAR_CFG_ENABLE;
    CFG(dcode->code39, ZBAR_CFG_MIN_LEN) = 1;
#endif
#ifdef ENABLE_CODE93
    dcode->code93.config = 1 << ZBAR_CFG_ENABLE;
#endif
#ifdef ENABLE_CODE128
    dcode->code128.config = 1 << ZBAR_CFG_ENABLE;
#endif
#ifdef ENABLE_PDF417
    dcode->pdf417.config = 1 << ZBAR_CFG_ENABLE;
#endif
#ifdef ENABLE_QRCODE
    dcode->qrf.config = 1 << ZBAR_CFG_ENABLE;
#endif

    zbar_decoder_reset(dcode);
    return(dcode);
}