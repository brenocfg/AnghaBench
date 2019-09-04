#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int zbar_symbol_type_t ;
struct TYPE_12__ {int* chars; int /*<<< orphan*/  epoch; TYPE_2__* segs; int /*<<< orphan*/  config_exp; int /*<<< orphan*/  config; } ;
struct TYPE_10__ {int idx; TYPE_3__ databar; } ;
typedef  TYPE_1__ zbar_decoder_t ;
struct TYPE_11__ {unsigned int finder; int exp; unsigned int color; unsigned int side; int partial; int count; unsigned int width; int /*<<< orphan*/  epoch; } ;
typedef  TYPE_2__ databar_segment_t ;
typedef  TYPE_3__ databar_decoder_t ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_CFG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZBAR_CFG_ENABLE ; 
 int ZBAR_NONE ; 
 int alloc_segment (TYPE_3__*) ; 
 int /*<<< orphan*/  dbprintf (int,char*,unsigned int,...) ; 
 int decode_char (TYPE_1__*,TYPE_2__*,int,int) ; 
 int decode_e (unsigned int,unsigned int,int) ; 
 int* finder_hash ; 
 unsigned int get_color (TYPE_1__*) ; 
 unsigned int pair_width (TYPE_1__*,int) ; 
 int /*<<< orphan*/  zassert (int,int,char*,...) ; 

__attribute__((used)) static inline zbar_symbol_type_t
decode_finder (zbar_decoder_t *dcode)
{
    databar_decoder_t *db = &dcode->databar;
    databar_segment_t *seg;
    unsigned e0 = pair_width(dcode, 1);
    unsigned e2 = pair_width(dcode, 3);
    unsigned e1, e3, s, finder, dir;
    int sig, iseg;
    dbprintf(2, "      databar: e0=%d e2=%d", e0, e2);
    if(e0 < e2) {
        unsigned e = e2 * 4;
        if(e < 15 * e0 || e > 34 * e0)
            return(ZBAR_NONE);
        dir = 0;
        e3 = pair_width(dcode, 4);
    }
    else {
        unsigned e = e0 * 4;
        if(e < 15 * e2 || e > 34 * e2)
            return(ZBAR_NONE);
        dir = 1;
        e2 = e0;
        e3 = pair_width(dcode, 0);
    }
    e1 = pair_width(dcode, 2);

    s = e1 + e3;
    dbprintf(2, " e1=%d e3=%d dir=%d s=%d", e1, e3, dir, s);
    if(s < 12)
        return(ZBAR_NONE);

    sig = ((decode_e(e3, s, 14) << 8) | (decode_e(e2, s, 14) << 4) |
           decode_e(e1, s, 14));
    dbprintf(2, " sig=%04x", sig & 0xfff);
    if(sig < 0 ||
       ((sig >> 4) & 0xf) < 8 ||
       ((sig >> 4) & 0xf) > 10 ||
       (sig & 0xf) >= 10 ||
       ((sig >> 8) & 0xf) >= 10 ||
       (((sig >> 8) + sig) & 0xf) != 10)
        return(ZBAR_NONE);

    finder = (finder_hash[(sig - (sig >> 5)) & 0x1f] +
              finder_hash[(sig >> 1) & 0x1f]) & 0x1f;
    dbprintf(2, " finder=%d", finder);
    if(finder == 0x1f ||
       !TEST_CFG((finder < 9) ? db->config : db->config_exp, ZBAR_CFG_ENABLE))
        return(ZBAR_NONE);

    zassert(finder >= 0, ZBAR_NONE, "dir=%d sig=%04x f=%d\n",
            dir, sig & 0xfff, finder);

    iseg = alloc_segment(db);
    if(iseg < 0)
        return(ZBAR_NONE);

    seg = db->segs + iseg;
    seg->finder = (finder >= 9) ? finder - 9 : finder;
    seg->exp = (finder >= 9);
    seg->color = get_color(dcode) ^ dir ^ 1;
    seg->side = dir;
    seg->partial = 0;
    seg->count = 1;
    seg->width = s;
    seg->epoch = db->epoch;

    int rc = decode_char(dcode, seg, 12 - dir, -1);
    if(!rc)
        seg->partial = 1;
    else
        db->epoch++;

    int i = (dcode->idx + 8 + dir) & 0xf;
    zassert(db->chars[i] == -1, ZBAR_NONE, "\n");
    db->chars[i] = iseg;
    return(rc);
}