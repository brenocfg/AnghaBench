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
typedef  int /*<<< orphan*/  zbar_symbol_type_t ;
typedef  int /*<<< orphan*/  zbar_decoder_t ;
typedef  int zbar_config_t ;

/* Variables and functions */
 int ZBAR_CFG_NUM ; 
 scalar_t__ decoder_get_configp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int decoder_set_config_bool (zbar_decoder_t *dcode,
                                           zbar_symbol_type_t sym,
                                           zbar_config_t cfg,
                                           int val)
{
    unsigned *config = (void*)decoder_get_configp(dcode, sym);
    if(!config || cfg >= ZBAR_CFG_NUM)
        return(1);

    if(!val)
        *config &= ~(1 << cfg);
    else if(val == 1)
        *config |= (1 << cfg);
    else
        return(1);

#ifdef ENABLE_EAN
    dcode->ean.enable = TEST_CFG(dcode->ean.ean13_config |
                                 dcode->ean.ean2_config |
                                 dcode->ean.ean5_config |
                                 dcode->ean.ean8_config |
                                 dcode->ean.upca_config |
                                 dcode->ean.upce_config |
                                 dcode->ean.isbn10_config |
                                 dcode->ean.isbn13_config,
                                 ZBAR_CFG_ENABLE);
#endif

    return(0);
}