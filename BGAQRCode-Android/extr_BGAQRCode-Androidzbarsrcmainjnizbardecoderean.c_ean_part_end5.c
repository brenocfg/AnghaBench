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
struct TYPE_6__ {int /*<<< orphan*/  ean5_config; } ;
typedef  TYPE_2__ ean_decoder_t ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_CFG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZBAR_CFG_ENABLE ; 
 char ZBAR_EAN5 ; 
 char ZBAR_NONE ; 
 int /*<<< orphan*/  dbprintf (int,char*,...) ; 
 unsigned char* parity_decode ; 

__attribute__((used)) static inline char ean_part_end5 (ean_decoder_t *ean,
                                  ean_pass_t *pass)
{
    if(!TEST_CFG(ean->ean5_config, ZBAR_CFG_ENABLE))
        return(ZBAR_NONE);

    /* extract parity bits */
    unsigned char par = ((pass->raw[1] & 0x10) |
                         (pass->raw[2] & 0x10) >> 1 |
                         (pass->raw[3] & 0x10) >> 2 |
                         (pass->raw[4] & 0x10) >> 3 |
                         (pass->raw[5] & 0x10) >> 4);
    /* calculate checksum */
    unsigned char chk = (((pass->raw[1] & 0x0f) +
                          (pass->raw[2] & 0x0f) * 3 +
                          (pass->raw[3] & 0x0f) +
                          (pass->raw[4] & 0x0f) * 3 +
                          (pass->raw[5] & 0x0f)) * 3) % 10;

    unsigned char parchk = parity_decode[par >> 1];
    if(par & 1)
        parchk >>= 4;
    parchk &= 0xf;
    dbprintf(2, " par=%x(%d) chk=%d", par, parchk, chk);
    if(parchk != chk)
        return(ZBAR_NONE);

    dbprintf(2, "\n");
    dbprintf(1, "decode5=%x%x%x%x%x\n",
             pass->raw[1] & 0xf, pass->raw[2] & 0xf,
             pass->raw[3] & 0xf, pass->raw[4] & 0xf,
             pass->raw[5] & 0xf);

    return(ZBAR_EAN5);
}