#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int zbar_symbol_type_t ;
typedef  int /*<<< orphan*/  zbar_decoder_t ;

/* Variables and functions */

__attribute__((used)) static inline const unsigned int*
decoder_get_configp (const zbar_decoder_t *dcode,
                     zbar_symbol_type_t sym)
{
    const unsigned int *config;
    switch(sym) {
#ifdef ENABLE_EAN
    case ZBAR_EAN13:
        config = &dcode->ean.ean13_config;
        break;

    case ZBAR_EAN2:
        config = &dcode->ean.ean2_config;
        break;

    case ZBAR_EAN5:
        config = &dcode->ean.ean5_config;
        break;

    case ZBAR_EAN8:
        config = &dcode->ean.ean8_config;
        break;

    case ZBAR_UPCA:
        config = &dcode->ean.upca_config;
        break;

    case ZBAR_UPCE:
        config = &dcode->ean.upce_config;
        break;

    case ZBAR_ISBN10:
        config = &dcode->ean.isbn10_config;
        break;

    case ZBAR_ISBN13:
        config = &dcode->ean.isbn13_config;
        break;
#endif

#ifdef ENABLE_I25
    case ZBAR_I25:
        config = &dcode->i25.config;
        break;
#endif

#ifdef ENABLE_DATABAR
    case ZBAR_DATABAR:
        config = &dcode->databar.config;
        break;
    case ZBAR_DATABAR_EXP:
        config = &dcode->databar.config_exp;
        break;
#endif

#ifdef ENABLE_CODABAR
    case ZBAR_CODABAR:
        config = &dcode->codabar.config;
        break;
#endif

#ifdef ENABLE_CODE39
    case ZBAR_CODE39:
        config = &dcode->code39.config;
        break;
#endif

#ifdef ENABLE_CODE93
    case ZBAR_CODE93:
        config = &dcode->code93.config;
        break;
#endif

#ifdef ENABLE_CODE128
    case ZBAR_CODE128:
        config = &dcode->code128.config;
        break;
#endif

#ifdef ENABLE_PDF417
    case ZBAR_PDF417:
        config = &dcode->pdf417.config;
        break;
#endif

#ifdef ENABLE_QRCODE
    case ZBAR_QRCODE:
        config = &dcode->qrf.config;
        break;
#endif

    default:
        config = NULL;
    }
    return(config);
}