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
typedef  int /*<<< orphan*/  AVMurMur3 ;

/* Variables and functions */
 int /*<<< orphan*/  av_murmur3_init_seeded (int /*<<< orphan*/ *,int) ; 

void av_murmur3_init(AVMurMur3 *c)
{
    // arbitrary random number as seed
    av_murmur3_init_seeded(c, 0x725acc55daddca55);
}