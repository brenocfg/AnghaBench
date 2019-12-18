#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int* linesize; scalar_t__* data; } ;
typedef  TYPE_1__ AVFrame ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,int) ; 

__attribute__((used)) static void copy_chroma(AVFrame *dst, AVFrame *src, int width, int height)
{
    int i, j;

    for (j = 1; j < 3; j++) {
        for (i = 0; i < height / 2; i++)
            memcpy(dst->data[j] + i * dst->linesize[j],
                   src->data[j] + i * src->linesize[j], width / 2);
    }
}