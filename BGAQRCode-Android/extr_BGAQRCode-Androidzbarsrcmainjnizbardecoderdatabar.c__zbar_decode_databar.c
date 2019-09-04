#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zbar_symbol_type_t ;
struct TYPE_11__ {int* chars; int /*<<< orphan*/  epoch; TYPE_2__* segs; } ;
struct TYPE_9__ {int idx; TYPE_3__ databar; } ;
typedef  TYPE_1__ zbar_decoder_t ;
struct TYPE_10__ {int partial; int finder; int side; int count; int /*<<< orphan*/  epoch; int /*<<< orphan*/  width; int /*<<< orphan*/  color; int /*<<< orphan*/  exp; } ;
typedef  TYPE_2__ databar_segment_t ;
typedef  TYPE_3__ databar_decoder_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZBAR_NONE ; 
 int alloc_segment (TYPE_3__*) ; 
 int /*<<< orphan*/  dbprintf (int,char*,...) ; 
 int /*<<< orphan*/  decode_char (TYPE_1__*,TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  decode_finder (TYPE_1__*) ; 
 int /*<<< orphan*/  zassert (int,int /*<<< orphan*/ ,char*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

zbar_symbol_type_t
_zbar_decode_databar (zbar_decoder_t *dcode)
{
    databar_decoder_t *db = &dcode->databar;
    databar_segment_t *seg, *pair;
    zbar_symbol_type_t sym;
    int iseg, i = dcode->idx & 0xf;

    sym = decode_finder(dcode);
    dbprintf(2, "\n");

    iseg = db->chars[i];
    if(iseg < 0)
        return(sym);

    db->chars[i] = -1;
    seg = db->segs + iseg;
    dbprintf(2, "        databar: i=%d part=%d f=%d(%x%x%x)",
             iseg, seg->partial, seg->finder, seg->exp, seg->color, seg->side);
    zassert(seg->finder >= 0, ZBAR_NONE, "i=%d f=%d(%x%x%x) part=%x\n",
            iseg, seg->finder, seg->exp, seg->color, seg->side, seg->partial);

    if(seg->partial) {
        pair = NULL;
        seg->side = !seg->side;
    }
    else {
        int jseg = alloc_segment(db);
        pair = db->segs + iseg;
        seg = db->segs + jseg;
        seg->finder = pair->finder;
        seg->exp = pair->exp;
        seg->color = pair->color;
        seg->side = !pair->side;
        seg->partial = 0;
        seg->count = 1;
        seg->width = pair->width;
        seg->epoch = db->epoch;
    }

    sym = decode_char(dcode, seg, 1, 1);
    if(!sym) {
        seg->finder = -1;
        if(pair)
            pair->partial = 1;
    }
    else
        db->epoch++;
    dbprintf(2, "\n");

    return(sym);
}