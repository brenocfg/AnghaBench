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
struct TYPE_6__ {int s4; } ;
struct TYPE_7__ {TYPE_1__ ean; } ;
typedef  TYPE_2__ zbar_decoder_t ;

/* Variables and functions */
 scalar_t__ ZBAR_BAR ; 
 int /*<<< orphan*/  dbprintf (int,char*,char,...) ; 
 int decode_e (unsigned int,int,int) ; 
 char* digits ; 
 scalar_t__ get_color (TYPE_2__*) ; 
 unsigned int get_width (TYPE_2__*,int) ; 
 int /*<<< orphan*/  zassert (int,int,char*,char,unsigned int,unsigned int,unsigned char,scalar_t__) ; 

__attribute__((used)) static inline signed char decode4 (zbar_decoder_t *dcode)
{
    signed char code;

    /* calculate similar edge measurements */
    unsigned e1 = ((get_color(dcode) == ZBAR_BAR)
                   ? get_width(dcode, 0) + get_width(dcode, 1)
                   : get_width(dcode, 2) + get_width(dcode, 3));
    unsigned e2 = get_width(dcode, 1) + get_width(dcode, 2);
    dbprintf(2, "\n        e1=%d e2=%d", e1, e2);

    if(dcode->ean.s4 < 6)
        return(-1);

    /* create compacted encoding for direct lookup */
    code = ((decode_e(e1, dcode->ean.s4, 7) << 2) |
             decode_e(e2, dcode->ean.s4, 7));
    if(code < 0)
        return(-1);
    dbprintf(2, " code=%x", code);

    /* 4 combinations require additional determinant (D2)
       E1E2 == 34 (0110)
       E1E2 == 43 (1001)
       E1E2 == 33 (0101)
       E1E2 == 44 (1010)
     */
    if((1 << code) & 0x0660) {
        unsigned char mid, alt;
        /* use sum of bar widths */
        unsigned d2 = ((get_color(dcode) == ZBAR_BAR)
                       ? get_width(dcode, 0) + get_width(dcode, 2)
                       : get_width(dcode, 1) + get_width(dcode, 3));
        d2 *= 7;
        mid = (((1 << code) & 0x0420)
                             ? 3     /* E1E2 in 33,44 */
                             : 4);   /* E1E2 in 34,43 */
        alt = d2 > (mid * dcode->ean.s4);
        if(alt)
            code = ((code >> 1) & 3) | 0x10; /* compress code space */
        dbprintf(2, " (d2=%d(%d) alt=%d)", d2, mid * dcode->ean.s4, alt);
    }
    dbprintf(2, " char=%02x", digits[(unsigned char)code]);
    zassert(code < 0x14, -1, "code=%02x e1=%x e2=%x s4=%x color=%x\n",
            code, e1, e2, dcode->ean.s4, get_color(dcode));
    return(code);
}