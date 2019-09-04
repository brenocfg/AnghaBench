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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {TYPE_1__* avctx; int /*<<< orphan*/  video_size; int /*<<< orphan*/  video; } ;
struct TYPE_4__ {int height; int width; } ;
typedef  int /*<<< orphan*/  GetByteContext ;
typedef  TYPE_2__ CDXLVideoContext ;

/* Variables and functions */
 int /*<<< orphan*/  bytestream2_get_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bytestream2_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void chunky2chunky(CDXLVideoContext *c, int linesize, uint8_t *out)
{
    GetByteContext gb;
    int y;

    bytestream2_init(&gb, c->video, c->video_size);
    for (y = 0; y < c->avctx->height; y++) {
        bytestream2_get_buffer(&gb, out + linesize * y, c->avctx->width * 3);
    }
}