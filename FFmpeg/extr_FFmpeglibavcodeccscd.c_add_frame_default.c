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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int* linesize; int /*<<< orphan*/ ** data; } ;
typedef  TYPE_1__ AVFrame ;

/* Variables and functions */
 int FFALIGN (int,int) ; 

__attribute__((used)) static void add_frame_default(AVFrame *f, const uint8_t *src,
                              int linelen, int height)
{
    int i, j, src_stride = FFALIGN(linelen, 4);
    uint8_t *dst = f->data[0];
    dst += (height - 1) * f->linesize[0];
    for (i = height; i; i--) {
        for (j = linelen; j; j--)
            *dst++ += *src++;
        src += src_stride - linelen;
        dst -= f->linesize[0] + linelen;
    }
}