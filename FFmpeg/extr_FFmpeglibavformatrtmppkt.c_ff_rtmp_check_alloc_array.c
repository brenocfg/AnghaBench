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
typedef  int /*<<< orphan*/  RTMPPacket ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/ * av_realloc_array (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int ff_rtmp_check_alloc_array(RTMPPacket **prev_pkt, int *nb_prev_pkt,
                              int channel)
{
    int nb_alloc;
    RTMPPacket *ptr;
    if (channel < *nb_prev_pkt)
        return 0;

    nb_alloc = channel + 16;
    // This can't use the av_reallocp family of functions, since we
    // would need to free each element in the array before the array
    // itself is freed.
    ptr = av_realloc_array(*prev_pkt, nb_alloc, sizeof(**prev_pkt));
    if (!ptr)
        return AVERROR(ENOMEM);
    memset(ptr + *nb_prev_pkt, 0, (nb_alloc - *nb_prev_pkt) * sizeof(*ptr));
    *prev_pkt = ptr;
    *nb_prev_pkt = nb_alloc;
    return 0;
}