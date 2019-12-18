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
struct TYPE_6__ {int* table_mv_index; int* table_mv_bits; int* table_mv_code; int n; } ;
struct TYPE_5__ {size_t mv_table_index; int /*<<< orphan*/  pb; } ;
typedef  TYPE_1__ MpegEncContext ;
typedef  TYPE_2__ MVTable ;

/* Variables and functions */
 TYPE_2__* ff_mv_tables ; 
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int,int) ; 

void ff_msmpeg4_encode_motion(MpegEncContext * s,
                                  int mx, int my)
{
    int code;
    MVTable *mv;

    /* modulo encoding */
    /* WARNING : you cannot reach all the MVs even with the modulo
       encoding. This is a somewhat strange compromise they took !!!  */
    if (mx <= -64)
        mx += 64;
    else if (mx >= 64)
        mx -= 64;
    if (my <= -64)
        my += 64;
    else if (my >= 64)
        my -= 64;

    mx += 32;
    my += 32;
    mv = &ff_mv_tables[s->mv_table_index];

    code = mv->table_mv_index[(mx << 6) | my];
    put_bits(&s->pb,
             mv->table_mv_bits[code],
             mv->table_mv_code[code]);
    if (code == mv->n) {
        /* escape : code literally */
        put_bits(&s->pb, 6, mx);
        put_bits(&s->pb, 6, my);
    }
}