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
struct TYPE_4__ {int /*<<< orphan*/  buf_alloc; } ;
typedef  TYPE_1__ zbar_decoder_t ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,long) ; 

void zbar_decoder_reset (zbar_decoder_t *dcode)
{
    memset(dcode, 0, (long)&dcode->buf_alloc - (long)dcode);
#ifdef ENABLE_EAN
    ean_reset(&dcode->ean);
#endif
#ifdef ENABLE_I25
    i25_reset(&dcode->i25);
#endif
#ifdef ENABLE_DATABAR
    databar_reset(&dcode->databar);
#endif
#ifdef ENABLE_CODABAR
    codabar_reset(&dcode->codabar);
#endif
#ifdef ENABLE_CODE39
    code39_reset(&dcode->code39);
#endif
#ifdef ENABLE_CODE93
    code93_reset(&dcode->code93);
#endif
#ifdef ENABLE_CODE128
    code128_reset(&dcode->code128);
#endif
#ifdef ENABLE_PDF417
    pdf417_reset(&dcode->pdf417);
#endif
#ifdef ENABLE_QRCODE
    qr_finder_reset(&dcode->qrf);
#endif
}