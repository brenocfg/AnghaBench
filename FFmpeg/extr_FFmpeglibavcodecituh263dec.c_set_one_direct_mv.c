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
typedef  int uint16_t ;
struct TYPE_6__ {int* block_index; int pp_time; int pb_time; int*** mv; int** direct_scale_mv; } ;
struct TYPE_5__ {int*** motion_val; } ;
typedef  TYPE_1__ Picture ;
typedef  TYPE_2__ MpegEncContext ;

/* Variables and functions */
 int tab_bias ; 
 unsigned int tab_size ; 

__attribute__((used)) static inline void set_one_direct_mv(MpegEncContext *s, Picture *p, int i)
{
    int xy           = s->block_index[i];
    uint16_t time_pp = s->pp_time;
    uint16_t time_pb = s->pb_time;
    int p_mx, p_my;

    p_mx = p->motion_val[0][xy][0];
    if ((unsigned)(p_mx + tab_bias) < tab_size) {
        s->mv[0][i][0] = s->direct_scale_mv[0][p_mx + tab_bias];
        s->mv[1][i][0] = s->direct_scale_mv[1][p_mx + tab_bias];
    } else {
        s->mv[0][i][0] = p_mx * time_pb / time_pp;
        s->mv[1][i][0] = p_mx * (time_pb - time_pp) / time_pp;
    }
    p_my = p->motion_val[0][xy][1];
    if ((unsigned)(p_my + tab_bias) < tab_size) {
        s->mv[0][i][1] = s->direct_scale_mv[0][p_my + tab_bias];
        s->mv[1][i][1] = s->direct_scale_mv[1][p_my + tab_bias];
    } else {
        s->mv[0][i][1] = p_my * time_pb / time_pp;
        s->mv[1][i][1] = p_my * (time_pb - time_pp) / time_pp;
    }
}