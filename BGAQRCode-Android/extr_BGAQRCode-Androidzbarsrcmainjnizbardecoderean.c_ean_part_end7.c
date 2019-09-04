#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int zbar_symbol_type_t ;
struct TYPE_5__ {int* raw; int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ ean_pass_t ;
struct TYPE_6__ {int /*<<< orphan*/  ean13_config; } ;
typedef  TYPE_2__ ean_decoder_t ;

/* Variables and functions */
 int EAN_LEFT ; 
 int EAN_RIGHT ; 
 int /*<<< orphan*/  STATE_REV ; 
 scalar_t__ TEST_CFG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZBAR_CFG_ENABLE ; 
 int ZBAR_EAN13 ; 
 int ZBAR_NONE ; 
 int ZBAR_UPCE ; 
 int /*<<< orphan*/  dbprintf (int,char*,...) ; 
 int* parity_decode ; 

__attribute__((used)) static inline zbar_symbol_type_t ean_part_end7 (ean_decoder_t *ean,
                                                ean_pass_t *pass,
                                                unsigned char fwd)
{
    /* calculate parity index */
    unsigned char par = ((fwd)
                         ? ((pass->raw[1] & 0x10) << 1 |
                            (pass->raw[2] & 0x10) |
                            (pass->raw[3] & 0x10) >> 1 |
                            (pass->raw[4] & 0x10) >> 2 |
                            (pass->raw[5] & 0x10) >> 3 |
                            (pass->raw[6] & 0x10) >> 4)
                         : ((pass->raw[1] & 0x10) >> 4 |
                            (pass->raw[2] & 0x10) >> 3 |
                            (pass->raw[3] & 0x10) >> 2 |
                            (pass->raw[4] & 0x10) >> 1 |
                            (pass->raw[5] & 0x10) |
                            (pass->raw[6] & 0x10) << 1));

    /* lookup parity combination */
    pass->raw[0] = parity_decode[par >> 1];
    if(par & 1)
        pass->raw[0] >>= 4;
    pass->raw[0] &= 0xf;
    dbprintf(2, " par=%02x(%x)", par, pass->raw[0]);

    if(pass->raw[0] == 0xf)
        /* invalid parity combination */
        return(ZBAR_NONE);

    if(!par == fwd) {
        unsigned char i;
        pass->state |= STATE_REV;
        /* reverse sampled digits */
        for(i = 1; i < 4; i++) {
            unsigned char tmp = pass->raw[i];
            pass->raw[i] = pass->raw[7 - i];
            pass->raw[7 - i] = tmp;
        }
    }

    dbprintf(2, "\n");
    dbprintf(1, "decode=%x%x%x%x%x%x%x(%02x)\n",
             pass->raw[0] & 0xf, pass->raw[1] & 0xf,
             pass->raw[2] & 0xf, pass->raw[3] & 0xf,
             pass->raw[4] & 0xf, pass->raw[5] & 0xf,
             pass->raw[6] & 0xf, par);

    if(TEST_CFG(ean->ean13_config, ZBAR_CFG_ENABLE)) {
        if(!par)
            return(ZBAR_EAN13 | EAN_RIGHT);
        if(par & 0x20)
            return(ZBAR_EAN13 | EAN_LEFT);
    }
    if(par && !(par & 0x20))
        return(ZBAR_UPCE);

    return(ZBAR_NONE);
}