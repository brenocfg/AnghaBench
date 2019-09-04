#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/ * avpriv_find_start_code (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int*) ; 

int ff_mpeg4video_split(AVCodecContext *avctx, const uint8_t *buf, int buf_size)
{
    uint32_t state = -1;
    const uint8_t *ptr = buf, *end = buf + buf_size;

    while (ptr < end) {
        ptr = avpriv_find_start_code(ptr, end, &state);
        if (state == 0x1B3 || state == 0x1B6)
            return ptr - 4 - buf;
    }

    return 0;
}