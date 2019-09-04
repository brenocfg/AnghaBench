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

/* Variables and functions */
 int /*<<< orphan*/ * av_packet_alloc () ; 
 int /*<<< orphan*/  av_packet_free (int /*<<< orphan*/ **) ; 
 scalar_t__ av_packet_ref (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

AVPacket *av_packet_clone(const AVPacket *src)
{
    AVPacket *ret = av_packet_alloc();

    if (!ret)
        return ret;

    if (av_packet_ref(ret, src))
        av_packet_free(&ret);

    return ret;
}