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
struct TYPE_3__ {int* linesize; scalar_t__* data; } ;
typedef  TYPE_1__ AVFrame ;

/* Variables and functions */
 unsigned int AV_RN16 (scalar_t__) ; 

__attribute__((used)) static int is_same1_16(AVFrame *frame, int x, int y,
                       unsigned s0, unsigned s1, unsigned s2, unsigned s3)
{
    unsigned c0 = AV_RN16(frame->data[0] + y * frame->linesize[0] + 2 * x);

    if (s0 == c0)
        return 1;
    return 0;
}