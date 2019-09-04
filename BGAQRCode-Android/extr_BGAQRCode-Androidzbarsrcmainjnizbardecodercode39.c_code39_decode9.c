#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int s9; int width; scalar_t__ direction; } ;
struct TYPE_7__ {TYPE_2__ code39; } ;
typedef  TYPE_1__ zbar_decoder_t ;
typedef  TYPE_2__ code39_decoder_t ;
struct TYPE_9__ {unsigned char chk; char fwd; char rev; } ;
typedef  TYPE_3__ char39_t ;

/* Variables and functions */
 unsigned char code39_decode1 (unsigned char,int /*<<< orphan*/ ,int) ; 
 TYPE_3__* code39_encodings ; 
 unsigned char* code39_hi ; 
 int /*<<< orphan*/  dbprintf (int,char*,unsigned char,unsigned char,char,char) ; 
 int /*<<< orphan*/  get_width (TYPE_1__*,unsigned char) ; 
 int /*<<< orphan*/  zassert (int,int,char*,unsigned char,unsigned char,...) ; 

__attribute__((used)) static inline signed char code39_decode9 (zbar_decoder_t *dcode)
{
    code39_decoder_t *dcode39 = &dcode->code39;

    if(dcode39->s9 < 9)
        return(-1);

    /* threshold bar width ratios */
    unsigned char i, enc = 0;
    for(i = 0; i < 5; i++) {
        enc = code39_decode1(enc, get_width(dcode, i), dcode39->s9);
        if(enc == 0xff)
            return(-1);
    }
    zassert(enc < 0x20, -1, " enc=%x s9=%x\n", enc, dcode39->s9);

    /* lookup first 5 encoded widths for coarse decode */
    unsigned char idx = code39_hi[enc];
    if(idx == 0xff)
        return(-1);

    /* encode remaining widths (NB first encoded width is lost) */
    for(; i < 9; i++) {
        enc = code39_decode1(enc, get_width(dcode, i), dcode39->s9);
        if(enc == 0xff)
            return(-1);
    }

    if((idx & 0xc0) == 0x80)
        idx = (idx & 0x3f) + ((enc >> 3) & 1);
    else if((idx & 0xc0) == 0xc0)
        idx = (idx & 0x3f) + ((enc >> 2) & 1);
    else if(idx & 0xc0)
        idx = (idx & 0x3f) + ((enc >> 2) & 3);
    zassert(idx < 0x2c, -1, " idx=%x enc=%x s9=%x\n", idx, enc, dcode39->s9);

    const char39_t *c = &code39_encodings[idx];
    dbprintf(2, " i=%02x chk=%02x c=%02x/%02x", idx, c->chk, c->fwd, c->rev);
    if(enc != c->chk)
        return(-1);

    dcode39->width = dcode39->s9;
    return((dcode39->direction) ? c->rev : c->fwd);
}