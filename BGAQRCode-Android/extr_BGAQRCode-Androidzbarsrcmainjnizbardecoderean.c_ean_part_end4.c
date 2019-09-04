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
typedef  int zbar_symbol_type_t ;
struct TYPE_3__ {int* raw; int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ ean_pass_t ;

/* Variables and functions */
 int EAN_LEFT ; 
 int EAN_RIGHT ; 
 int /*<<< orphan*/  STATE_REV ; 
 int ZBAR_EAN8 ; 
 int ZBAR_NONE ; 
 int /*<<< orphan*/  dbprintf (int,char*,...) ; 

__attribute__((used)) static inline zbar_symbol_type_t ean_part_end4 (ean_pass_t *pass,
                                                unsigned char fwd)
{
    /* extract parity bits */
    unsigned char par = ((pass->raw[1] & 0x10) >> 1 |
                         (pass->raw[2] & 0x10) >> 2 |
                         (pass->raw[3] & 0x10) >> 3 |
                         (pass->raw[4] & 0x10) >> 4);

    dbprintf(2, " par=%x", par);
    if(par && par != 0xf)
        /* invalid parity combination */
        return(ZBAR_NONE);

    if(!par == fwd) {
        /* reverse sampled digits */
        unsigned char tmp = pass->raw[1];
        pass->state |= STATE_REV;
        pass->raw[1] = pass->raw[4];
        pass->raw[4] = tmp;
        tmp = pass->raw[2];
        pass->raw[2] = pass->raw[3];
        pass->raw[3] = tmp;
    }

    dbprintf(2, "\n");
    dbprintf(1, "decode4=%x%x%x%x\n",
             pass->raw[1] & 0xf, pass->raw[2] & 0xf,
             pass->raw[3] & 0xf, pass->raw[4] & 0xf);
    if(!par)
        return(ZBAR_EAN8 | EAN_RIGHT);
    return(ZBAR_EAN8 | EAN_LEFT);
}