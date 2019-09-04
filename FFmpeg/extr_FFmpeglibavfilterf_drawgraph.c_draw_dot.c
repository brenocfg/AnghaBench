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
 int /*<<< orphan*/  AV_WN32 (scalar_t__,int) ; 

__attribute__((used)) static inline void draw_dot(int fg, int x, int y, AVFrame *out)
{
    AV_WN32(out->data[0] + y * out->linesize[0] + x * 4, fg);
}