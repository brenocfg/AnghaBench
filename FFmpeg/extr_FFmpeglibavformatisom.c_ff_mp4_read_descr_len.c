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
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int avio_r8 (int /*<<< orphan*/ *) ; 

int ff_mp4_read_descr_len(AVIOContext *pb)
{
    int len = 0;
    int count = 4;
    while (count--) {
        int c = avio_r8(pb);
        len = (len << 7) | (c & 0x7f);
        if (!(c & 0x80))
            break;
    }
    return len;
}