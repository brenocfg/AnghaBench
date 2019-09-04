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
struct TYPE_6__ {int block_type; void** sb_hybrid; int short_start; scalar_t__ switch_point; } ;
struct TYPE_5__ {int sample_rate_index; } ;
typedef  TYPE_1__ MPADecodeContext ;
typedef  void* INTFLOAT ;
typedef  TYPE_2__ GranuleDef ;

/* Variables and functions */
 int** band_size_short ; 
 int /*<<< orphan*/  memcpy (void**,void**,int) ; 

__attribute__((used)) static void reorder_block(MPADecodeContext *s, GranuleDef *g)
{
    int i, j, len;
    INTFLOAT *ptr, *dst, *ptr1;
    INTFLOAT tmp[576];

    if (g->block_type != 2)
        return;

    if (g->switch_point) {
        if (s->sample_rate_index != 8)
            ptr = g->sb_hybrid + 36;
        else
            ptr = g->sb_hybrid + 72;
    } else {
        ptr = g->sb_hybrid;
    }

    for (i = g->short_start; i < 13; i++) {
        len  = band_size_short[s->sample_rate_index][i];
        ptr1 = ptr;
        dst  = tmp;
        for (j = len; j > 0; j--) {
            *dst++ = ptr[0*len];
            *dst++ = ptr[1*len];
            *dst++ = ptr[2*len];
            ptr++;
        }
        ptr += 2 * len;
        memcpy(ptr1, tmp, len * 3 * sizeof(*ptr1));
    }
}