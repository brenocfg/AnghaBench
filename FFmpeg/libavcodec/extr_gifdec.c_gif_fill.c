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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int* linesize; int height; scalar_t__* data; } ;
typedef  TYPE_1__ AVFrame ;

/* Variables and functions */

__attribute__((used)) static void gif_fill(AVFrame *picture, uint32_t color)
{
    uint32_t *p = (uint32_t *)picture->data[0];
    uint32_t *p_end = p + (picture->linesize[0] / sizeof(uint32_t)) * picture->height;

    for (; p < p_end; p++)
        *p = color;
}