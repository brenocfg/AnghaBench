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
typedef  int /*<<< orphan*/  VIDEOHDR ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */

__attribute__((used)) static void dump_videohdr(AVFormatContext *s, VIDEOHDR *vhdr)
{
#ifdef DEBUG
    av_log(s, AV_LOG_DEBUG, "VIDEOHDR\n");
    dstruct(s, vhdr, lpData, "p");
    dstruct(s, vhdr, dwBufferLength, "lu");
    dstruct(s, vhdr, dwBytesUsed, "lu");
    dstruct(s, vhdr, dwTimeCaptured, "lu");
    dstruct(s, vhdr, dwUser, "lu");
    dstruct(s, vhdr, dwFlags, "lu");
    dstruct(s, vhdr, dwReserved[0], "lu");
    dstruct(s, vhdr, dwReserved[1], "lu");
    dstruct(s, vhdr, dwReserved[2], "lu");
    dstruct(s, vhdr, dwReserved[3], "lu");
#endif
}