#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {unsigned int s8; int /*<<< orphan*/  character; int /*<<< orphan*/  direction; } ;
struct TYPE_7__ {TYPE_1__ pdf417; int /*<<< orphan*/  buf; } ;
typedef  TYPE_2__ zbar_decoder_t ;

/* Variables and functions */
 long PDF417_HASH_MASK ; 
 short PDF417_STOP ; 
 scalar_t__ ZBAR_SPACE ; 
 int /*<<< orphan*/  _zbar_decoder_buf_dump (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbprintf (int,char*,short,...) ; 
 char decode_e (scalar_t__,unsigned int,int) ; 
 scalar_t__ get_color (TYPE_2__*) ; 
 scalar_t__ get_width (TYPE_2__*,int) ; 
 short* pdf417_hash ; 
 int /*<<< orphan*/  zassert (int,int,char*,int /*<<< orphan*/ ,long,int,short,...) ; 

__attribute__((used)) static inline signed short pdf417_decode8 (zbar_decoder_t *dcode)
{
    /* build edge signature of character
     * from similar edge measurements
     */
    unsigned s = dcode->pdf417.s8;
    dbprintf(2, " s=%d ", s);
    if(s < 8)
        return(-1);

    long sig = 0;
    signed char e;
    unsigned char i;
    for(i = 0; i < 7; i++) {
        if(get_color(dcode) == ZBAR_SPACE)
            e = decode_e(get_width(dcode, i) +
                         get_width(dcode, i + 1), s, 17);
        else
            e = decode_e(get_width(dcode, 7 - i) +
                         get_width(dcode, 6 - i), s, 17);
        dbprintf(4, "%x", e);
        if(e < 0 || e > 8)
            return(-1);
        sig = (sig << 3) ^ e;
    }
    dbprintf(2, " sig=%06lx", sig);

    /* determine cluster number */
    int clst = ((sig & 7) - ((sig >> 3) & 7) +
                ((sig >> 12) & 7) - ((sig >> 15) & 7));
    if(clst < 0)
        clst += 9;
    dbprintf(2, " k=%d", clst);
    zassert(clst >= 0 && clst < 9, -1, "dir=%x sig=%lx k=%x %s\n",
            dcode->pdf417.direction, sig, clst,
            _zbar_decoder_buf_dump(dcode->buf, dcode->pdf417.character));

    if(clst != 0 && clst != 3 && clst != 6) {
        if(get_color(dcode) && clst == 7 && sig == 0x080007)
            return(PDF417_STOP);
        return(-1);
    }

    signed short g[3];
    sig &= 0x3ffff;
    g[0] = pdf417_hash[(sig - (sig >> 10)) & PDF417_HASH_MASK];
    g[1] = pdf417_hash[((sig >> 8) - sig) & PDF417_HASH_MASK];
    g[2] = pdf417_hash[((sig >> 14) - (sig >> 1)) & PDF417_HASH_MASK];
    zassert(g[0] >= 0 && g[1] >= 0 && g[2] >= 0, -1,
            "dir=%x sig=%lx k=%x g0=%03x g1=%03x g2=%03x %s\n",
            dcode->pdf417.direction, sig, clst, g[0], g[1], g[2],
            _zbar_decoder_buf_dump(dcode->buf, dcode->pdf417.character));

    unsigned short c = (g[0] + g[1] + g[2]) & PDF417_HASH_MASK;
    dbprintf(2, " g0=%x g1=%x g2=%x c=%03d(%d)",
             g[0], g[1], g[2], c & 0x3ff, c >> 10);
    return(c);
}