#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {int width; int dirty; int len; int start; } ;
struct TYPE_5__ {int /*<<< orphan*/  diff_lines; } ;
typedef  TYPE_1__ FlashSV2Context ;
typedef  TYPE_2__ Block ;

/* Variables and functions */
 scalar_t__ memcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int compare_sl(FlashSV2Context * s, Block * b, const uint8_t * src,
                      uint8_t * frame, uint8_t * key, int y, int keyframe)
{
    if (memcmp(src, frame, b->width * 3) != 0) {
        b->dirty = 1;
        memcpy(frame, src, b->width * 3);
#ifndef FLASHSV2_DUMB
        s->diff_lines++;
#endif
    }
    if (memcmp(src, key, b->width * 3) != 0) {
        if (b->len == 0)
            b->start = y;
        b->len = y + 1 - b->start;
    }
    return 0;
}