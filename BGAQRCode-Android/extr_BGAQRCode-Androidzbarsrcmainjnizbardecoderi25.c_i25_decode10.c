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
struct TYPE_6__ {unsigned char s10; scalar_t__ direction; } ;
struct TYPE_5__ {TYPE_2__ i25; } ;
typedef  TYPE_1__ zbar_decoder_t ;
typedef  TYPE_2__ i25_decoder_t ;

/* Variables and functions */
 int /*<<< orphan*/  dbprintf (int,char*,...) ; 
 int /*<<< orphan*/  get_width (TYPE_1__*,unsigned char) ; 
 unsigned char i25_decode1 (unsigned char,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline unsigned char i25_decode10 (zbar_decoder_t *dcode,
                                          unsigned char offset)
{
    i25_decoder_t *dcode25 = &dcode->i25;
    dbprintf(2, " s=%d", dcode25->s10);
    if(dcode25->s10 < 10)
        return(0xff);

    /* threshold bar width ratios */
    unsigned char enc = 0, par = 0;
    signed char i;
    for(i = 8; i >= 0; i -= 2) {
        unsigned char j = offset + ((dcode25->direction) ? i : 8 - i);
        enc = i25_decode1(enc, get_width(dcode, j), dcode25->s10);
        if(enc == 0xff)
            return(0xff);
        if(enc & 1)
            par++;
    }

    dbprintf(2, " enc=%02x par=%x", enc, par);

    /* parity check */
    if(par != 2) {
        dbprintf(2, " [bad parity]");
        return(0xff);
    }

    /* decode binary weights */
    enc &= 0xf;
    if(enc & 8) {
        if(enc == 12)
            enc = 0;
        else if(--enc > 9) {
            dbprintf(2, " [invalid encoding]");
            return(0xff);
        }
    }

    dbprintf(2, " => %x", enc);
    return(enc);
}