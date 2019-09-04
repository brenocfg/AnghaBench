#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zbar_symbol_type_t ;
struct TYPE_8__ {unsigned int eoffs; unsigned int len; unsigned int* pos; unsigned int boffs; } ;
struct TYPE_10__ {unsigned int s5; TYPE_1__ line; } ;
struct TYPE_9__ {scalar_t__ buflen; scalar_t__ direction; TYPE_3__ qrf; } ;
typedef  TYPE_2__ zbar_decoder_t ;
typedef  TYPE_3__ qr_finder_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZBAR_QRCODE ; 
 scalar_t__ ZBAR_SPACE ; 
 int /*<<< orphan*/  dbprintf (int,char*,...) ; 
 int decode_e (int /*<<< orphan*/ ,unsigned int,int) ; 
 scalar_t__ get_color (TYPE_2__*) ; 
 unsigned int get_width (TYPE_2__*,int) ; 
 int /*<<< orphan*/  pair_width (TYPE_2__*,int) ; 

zbar_symbol_type_t _zbar_find_qr (zbar_decoder_t *dcode)
{
    qr_finder_t *qrf = &dcode->qrf;
    unsigned s, qz, w;
    int ei;

    /* update latest finder pattern width */
    qrf->s5 -= get_width(dcode, 6);
    qrf->s5 += get_width(dcode, 1);
    s = qrf->s5;

    /*TODO: The 2005 standard allows reflectance-reversed codes (light on dark
       instead of dark on light).
      If we find finder patterns with the opposite polarity, we should invert
       the final binarized image and use them to search for QR codes in that.*/
    if(get_color(dcode) != ZBAR_SPACE || s < 7)
        return(0);

    dbprintf(2, "    qrf: s=%d", s);

    ei = decode_e(pair_width(dcode, 1), s, 7);
    dbprintf(2, " %d", ei);
    if(ei)
        goto invalid;

    ei = decode_e(pair_width(dcode, 2), s, 7);
    dbprintf(2, "%d", ei);
    if(ei != 2)
        goto invalid;

    ei = decode_e(pair_width(dcode, 3), s, 7);
    dbprintf(2, "%d", ei);
    if(ei != 2)
        goto invalid;

    ei = decode_e(pair_width(dcode, 4), s, 7);
    dbprintf(2, "%d", ei);
    if(ei)
        goto invalid;

    /* valid QR finder symbol
     * mark positions needed by decoder
     */
    qz = get_width(dcode, 0);
    w = get_width(dcode, 1);
    qrf->line.eoffs = qz + (w + 1) / 2;
    qrf->line.len = qz + w + get_width(dcode, 2);
    qrf->line.pos[0] = qrf->line.len + get_width(dcode, 3);
    qrf->line.pos[1] = qrf->line.pos[0];
    w = get_width(dcode, 5);
    qrf->line.boffs = qrf->line.pos[0] + get_width(dcode, 4) + (w + 1) / 2;

    dbprintf(2, " boff=%d pos=%d len=%d eoff=%d [valid]\n",
             qrf->line.boffs, qrf->line.pos[0], qrf->line.len,
             qrf->line.eoffs);

    dcode->direction = 0;
    dcode->buflen = 0;
    return(ZBAR_QRCODE);

invalid:
    dbprintf(2, " [invalid]\n");
    return(0);
}