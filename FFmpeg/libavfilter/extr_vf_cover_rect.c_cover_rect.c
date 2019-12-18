#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_8__ {int* linesize; int /*<<< orphan*/ ** data; } ;
struct TYPE_7__ {TYPE_1__* cover_frame; } ;
struct TYPE_6__ {int /*<<< orphan*/ * linesize; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/ ** data; } ;
typedef  TYPE_2__ CoverContext ;
typedef  TYPE_3__ AVFrame ;

/* Variables and functions */
 int AV_CEIL_RSHIFT (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void cover_rect(CoverContext *cover, AVFrame *in, int offx, int offy)
{
    int x, y, p;

    for (p = 0; p < 3; p++) {
        uint8_t *data = in->data[p] + (offx>>!!p) + (offy>>!!p) * in->linesize[p];
        const uint8_t *src = cover->cover_frame->data[p];
        int w = AV_CEIL_RSHIFT(cover->cover_frame->width , !!p);
        int h = AV_CEIL_RSHIFT(cover->cover_frame->height, !!p);
        for (y = 0; y < h; y++) {
            for (x = 0; x < w; x++) {
                data[x] = src[x];
            }
            data += in->linesize[p];
            src += cover->cover_frame->linesize[p];
        }
    }
}