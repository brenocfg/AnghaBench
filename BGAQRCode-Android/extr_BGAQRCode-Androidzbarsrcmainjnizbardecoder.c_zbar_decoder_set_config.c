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
typedef  scalar_t__ zbar_symbol_type_t ;
typedef  int /*<<< orphan*/  zbar_decoder_t ;
typedef  scalar_t__ zbar_config_t ;

/* Variables and functions */
 scalar_t__ ZBAR_CFG_MAX_LEN ; 
 scalar_t__ ZBAR_CFG_MIN_LEN ; 
 scalar_t__ ZBAR_CFG_NUM ; 
#define  ZBAR_CODABAR 144 
#define  ZBAR_CODE128 143 
#define  ZBAR_CODE39 142 
#define  ZBAR_CODE93 141 
#define  ZBAR_DATABAR 140 
#define  ZBAR_DATABAR_EXP 139 
#define  ZBAR_EAN13 138 
#define  ZBAR_EAN2 137 
#define  ZBAR_EAN5 136 
#define  ZBAR_EAN8 135 
#define  ZBAR_I25 134 
#define  ZBAR_ISBN10 133 
#define  ZBAR_ISBN13 132 
 scalar_t__ ZBAR_NONE ; 
#define  ZBAR_PDF417 131 
#define  ZBAR_QRCODE 130 
#define  ZBAR_UPCA 129 
#define  ZBAR_UPCE 128 
 int decoder_set_config_bool (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int) ; 
 int decoder_set_config_int (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int) ; 

int zbar_decoder_set_config (zbar_decoder_t *dcode,
                             zbar_symbol_type_t sym,
                             zbar_config_t cfg,
                             int val)
{
    if(sym == ZBAR_NONE) {
        static const zbar_symbol_type_t all[] = {
	    ZBAR_EAN13, ZBAR_EAN2, ZBAR_EAN5, ZBAR_EAN8,
            ZBAR_UPCA, ZBAR_UPCE, ZBAR_ISBN10, ZBAR_ISBN13,
            ZBAR_I25, ZBAR_DATABAR, ZBAR_DATABAR_EXP, ZBAR_CODABAR,
	    ZBAR_CODE39, ZBAR_CODE93, ZBAR_CODE128, ZBAR_QRCODE, 
	    ZBAR_PDF417, 0
        };
        const zbar_symbol_type_t *symp;
        for(symp = all; *symp; symp++)
            zbar_decoder_set_config(dcode, *symp, cfg, val);
        return(0);
    }

    if(cfg >= 0 && cfg < ZBAR_CFG_NUM)
        return(decoder_set_config_bool(dcode, sym, cfg, val));
    else if(cfg >= ZBAR_CFG_MIN_LEN && cfg <= ZBAR_CFG_MAX_LEN)
        return(decoder_set_config_int(dcode, sym, cfg, val));
    else
        return(1);
}