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
typedef  int /*<<< orphan*/  AVPacket ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 int ff_audio_rechunk_interleave (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mxf_compare_timestamps ; 
 int /*<<< orphan*/  mxf_interleave_get_packet ; 

__attribute__((used)) static int mxf_interleave(AVFormatContext *s, AVPacket *out, AVPacket *pkt, int flush)
{
    return ff_audio_rechunk_interleave(s, out, pkt, flush,
                               mxf_interleave_get_packet, mxf_compare_timestamps);
}