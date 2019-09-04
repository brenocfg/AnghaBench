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
struct TYPE_3__ {scalar_t__ s6; scalar_t__ idx; scalar_t__ lock; int /*<<< orphan*/  w; } ;
typedef  TYPE_1__ zbar_decoder_t ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void zbar_decoder_new_scan (zbar_decoder_t *dcode)
{
    /* soft reset decoder */
    memset(dcode->w, 0, sizeof(dcode->w));
    dcode->lock = 0;
    dcode->idx = 0;
    dcode->s6 = 0;
#ifdef ENABLE_EAN
    ean_new_scan(&dcode->ean);
#endif
#ifdef ENABLE_I25
    i25_reset(&dcode->i25);
#endif
#ifdef ENABLE_DATABAR
    databar_new_scan(&dcode->databar);
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