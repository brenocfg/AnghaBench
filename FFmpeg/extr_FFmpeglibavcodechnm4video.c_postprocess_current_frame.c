#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_5__ {TYPE_1__* priv_data; } ;
struct TYPE_4__ {int height; int width; int /*<<< orphan*/ * current; int /*<<< orphan*/ * processed; } ;
typedef  TYPE_1__ Hnm4VideoContext ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */

__attribute__((used)) static void postprocess_current_frame(AVCodecContext *avctx)
{
    Hnm4VideoContext *hnm = avctx->priv_data;
    uint32_t x, y, src_x, src_y;

    for (y = 0; y < hnm->height; y++) {
        src_y = y - (y % 2);
        src_x = src_y * hnm->width + (y % 2);
        for (x = 0; x < hnm->width; x++) {
            hnm->processed[(y * hnm->width) + x] = hnm->current[src_x];
            src_x += 2;
        }
    }
}