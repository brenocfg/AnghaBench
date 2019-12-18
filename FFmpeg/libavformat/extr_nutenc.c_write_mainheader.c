#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_9__ {int version; int minor_version; int max_distance; int time_base_count; int header_count; int* header_len; int flags; int /*<<< orphan*/ * header; TYPE_3__* frame_code; TYPE_2__* time_base; TYPE_1__* avf; } ;
struct TYPE_8__ {int pts_delta; int size_mul; int stream_id; int size_lsb; int header_idx; int flags; } ;
struct TYPE_7__ {int num; int den; } ;
struct TYPE_6__ {int nb_streams; } ;
typedef  TYPE_4__ NUTContext ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ff_put_v (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  put_s (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void write_mainheader(NUTContext *nut, AVIOContext *bc)
{
    int i, j, tmp_pts, tmp_flags, tmp_stream, tmp_mul, tmp_size, tmp_fields,
        tmp_head_idx;
    int64_t tmp_match;

    ff_put_v(bc, nut->version);
    if (nut->version > 3)
        ff_put_v(bc, nut->minor_version = 1);
    ff_put_v(bc, nut->avf->nb_streams);
    ff_put_v(bc, nut->max_distance);
    ff_put_v(bc, nut->time_base_count);

    for (i = 0; i < nut->time_base_count; i++) {
        ff_put_v(bc, nut->time_base[i].num);
        ff_put_v(bc, nut->time_base[i].den);
    }

    tmp_pts      = 0;
    tmp_mul      = 1;
    tmp_stream   = 0;
    tmp_match    = 1 - (1LL << 62);
    tmp_head_idx = 0;
    for (i = 0; i < 256; ) {
        tmp_fields = 0;
        tmp_size   = 0;
//        tmp_res=0;
        if (tmp_pts      != nut->frame_code[i].pts_delta ) tmp_fields = 1;
        if (tmp_mul      != nut->frame_code[i].size_mul  ) tmp_fields = 2;
        if (tmp_stream   != nut->frame_code[i].stream_id ) tmp_fields = 3;
        if (tmp_size     != nut->frame_code[i].size_lsb  ) tmp_fields = 4;
//        if (tmp_res    != nut->frame_code[i].res            ) tmp_fields=5;
        if (tmp_head_idx != nut->frame_code[i].header_idx) tmp_fields = 8;

        tmp_pts    = nut->frame_code[i].pts_delta;
        tmp_flags  = nut->frame_code[i].flags;
        tmp_stream = nut->frame_code[i].stream_id;
        tmp_mul    = nut->frame_code[i].size_mul;
        tmp_size   = nut->frame_code[i].size_lsb;
//        tmp_res   = nut->frame_code[i].res;
        tmp_head_idx = nut->frame_code[i].header_idx;

        for (j = 0; i < 256; j++, i++) {
            if (i == 'N') {
                j--;
                continue;
            }
            if (nut->frame_code[i].pts_delta  != tmp_pts      ||
                nut->frame_code[i].flags      != tmp_flags    ||
                nut->frame_code[i].stream_id  != tmp_stream   ||
                nut->frame_code[i].size_mul   != tmp_mul      ||
                nut->frame_code[i].size_lsb   != tmp_size + j ||
//              nut->frame_code[i].res        != tmp_res      ||
                nut->frame_code[i].header_idx != tmp_head_idx)
                break;
        }
        if (j != tmp_mul - tmp_size)
            tmp_fields = 6;

        ff_put_v(bc, tmp_flags);
        ff_put_v(bc, tmp_fields);
        if (tmp_fields > 0) put_s(bc, tmp_pts);
        if (tmp_fields > 1) ff_put_v(bc, tmp_mul);
        if (tmp_fields > 2) ff_put_v(bc, tmp_stream);
        if (tmp_fields > 3) ff_put_v(bc, tmp_size);
        if (tmp_fields > 4) ff_put_v(bc, 0 /*tmp_res*/);
        if (tmp_fields > 5) ff_put_v(bc, j);
        if (tmp_fields > 6) ff_put_v(bc, tmp_match);
        if (tmp_fields > 7) ff_put_v(bc, tmp_head_idx);
    }
    ff_put_v(bc, nut->header_count - 1);
    for (i = 1; i < nut->header_count; i++) {
        ff_put_v(bc, nut->header_len[i]);
        avio_write(bc, nut->header[i], nut->header_len[i]);
    }
    // flags had been effectively introduced in version 4
    if (nut->version > 3)
        ff_put_v(bc, nut->flags);
}