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
 int AVERROR_EOF ; 
 scalar_t__ avio_feof (int /*<<< orphan*/ *) ; 
 int avio_rl16 (int /*<<< orphan*/ *) ; 
 int avio_rl32 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int get_swf_tag(AVIOContext *pb, int *len_ptr)
{
    int tag, len;

    if (avio_feof(pb))
        return AVERROR_EOF;

    tag = avio_rl16(pb);
    len = tag & 0x3f;
    tag = tag >> 6;
    if (len == 0x3f) {
        len = avio_rl32(pb);
    }
    *len_ptr = len;
    return tag;
}