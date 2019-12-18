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
struct cs4297a_state {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int drain_adc(struct cs4297a_state *s, int nonblock)
{
        /* This routine serves no purpose currently - any samples
           sitting in the receive queue will just be processed by the
           background consumer.  This would be different if DMA
           actually stopped when there were no clients. */
	return 0;
}