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
struct ogg_stream {int nsegs; int* segments; } ;

/* Variables and functions */

__attribute__((used)) static int ogg_page_packets(struct ogg_stream *os)
{
    int i;
    int packets = 0;
    for (i = 0; i < os->nsegs; i++)
        if (os->segments[i] < 255)
            packets++;
    return packets;
}