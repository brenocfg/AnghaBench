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
struct TYPE_5__ {int* raw; } ;
typedef  TYPE_1__ ean_pass_t ;
struct TYPE_6__ {int /*<<< orphan*/  ean2_config; } ;
typedef  TYPE_2__ ean_decoder_t ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_CFG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZBAR_CFG_ENABLE ; 
 char ZBAR_EAN2 ; 
 char ZBAR_NONE ; 
 int /*<<< orphan*/  dbprintf (int,char*,...) ; 

__attribute__((used)) static inline char ean_part_end2 (ean_decoder_t *ean,
                                  ean_pass_t *pass)
{
    if(!TEST_CFG(ean->ean2_config, ZBAR_CFG_ENABLE))
        return(ZBAR_NONE);

    /* extract parity bits */
    unsigned char par = ((pass->raw[1] & 0x10) >> 3 |
                         (pass->raw[2] & 0x10) >> 4);
    /* calculate "checksum" */
    unsigned char chk = ~((pass->raw[1] & 0xf) * 10 +
                          (pass->raw[2] & 0xf)) & 0x3;
    dbprintf(2, " par=%x chk=%x", par, chk);
    if(par != chk)
        return(ZBAR_NONE);

    dbprintf(2, "\n");
    dbprintf(1, "decode2=%x%x\n",
             pass->raw[1] & 0xf, pass->raw[2] & 0xf);
    return(ZBAR_EAN2);
}