#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_17__ {TYPE_4__* oc; } ;
struct TYPE_11__ {int** gain; } ;
struct TYPE_16__ {TYPE_2__* ch; TYPE_1__ coup; } ;
struct TYPE_15__ {unsigned int* ret; } ;
struct TYPE_13__ {int sbr; } ;
struct TYPE_14__ {TYPE_3__ m4ac; } ;
struct TYPE_12__ {int* ret; } ;
typedef  TYPE_5__ SingleChannelElement ;
typedef  TYPE_6__ ChannelElement ;
typedef  TYPE_7__ AACContext ;

/* Variables and functions */
 int* cce_scale_fixed ; 

__attribute__((used)) static void apply_independent_coupling_fixed(AACContext *ac,
                                       SingleChannelElement *target,
                                       ChannelElement *cce, int index)
{
    int i, c, shift, round, tmp;
    const int gain = cce->coup.gain[index][0];
    const int *src = cce->ch[0].ret;
    unsigned int *dest = target->ret;
    const int len = 1024 << (ac->oc[1].m4ac.sbr == 1);

    c = cce_scale_fixed[gain & 7];
    shift = (gain-1024) >> 3;
    if (shift < -31) {
        return;
    } else if (shift < 0) {
        shift = -shift;
        round = 1 << (shift - 1);

        for (i = 0; i < len; i++) {
            tmp = (int)(((int64_t)src[i] * c + (int64_t)0x1000000000) >> 37);
            dest[i] += (tmp + round) >> shift;
        }
    }
    else {
      for (i = 0; i < len; i++) {
          tmp = (int)(((int64_t)src[i] * c + (int64_t)0x1000000000) >> 37);
          dest[i] += tmp * (1U << shift);
      }
    }
}