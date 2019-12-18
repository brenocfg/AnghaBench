#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int ptrdiff_t ;
struct TYPE_3__ {int* qtable; } ;
typedef  TYPE_1__ TgqContext ;

/* Variables and functions */
 int av_clip_uint8 (int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int,int) ; 

__attribute__((used)) static inline void tgq_dconly(TgqContext *s, unsigned char *dst,
                              ptrdiff_t dst_stride, int dc)
{
    int level = av_clip_uint8((dc*s->qtable[0] + 2056) >> 4);
    int j;
    for (j = 0; j < 8; j++)
        memset(dst + j * dst_stride, level, 8);
}