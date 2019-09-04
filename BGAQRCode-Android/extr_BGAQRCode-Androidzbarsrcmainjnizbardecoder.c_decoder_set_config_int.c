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
typedef  int /*<<< orphan*/  zbar_config_t ;

/* Variables and functions */

__attribute__((used)) static inline int decoder_set_config_int (zbar_decoder_t *dcode,
                                          zbar_symbol_type_t sym,
                                          zbar_config_t cfg,
                                          int val)
{
    switch(sym) {

#ifdef ENABLE_I25
    case ZBAR_I25:
        CFG(dcode->i25, cfg) = val;
        break;
#endif
#ifdef ENABLE_CODABAR
    case ZBAR_CODABAR:
        CFG(dcode->codabar, cfg) = val;
        break;
#endif
#ifdef ENABLE_CODE39
    case ZBAR_CODE39:
        CFG(dcode->code39, cfg) = val;
        break;
#endif
#ifdef ENABLE_CODE93
    case ZBAR_CODE93:
        CFG(dcode->code93, cfg) = val;
        break;
#endif
#ifdef ENABLE_CODE128
    case ZBAR_CODE128:
        CFG(dcode->code128, cfg) = val;
        break;
#endif
#ifdef ENABLE_PDF417
    case ZBAR_PDF417:
        CFG(dcode->pdf417, cfg) = val;
        break;
#endif

    default:
        return(1);
    }
    return(0);
}