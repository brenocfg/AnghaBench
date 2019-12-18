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
struct efx_channel {int event_test_cpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFX_CHANNEL_MAGIC_TEST (struct efx_channel*) ; 
 int /*<<< orphan*/  efx_magic_event (struct efx_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_wmb () ; 

void efx_nic_event_test_start(struct efx_channel *channel)
{
	channel->event_test_cpu = -1;
	smp_wmb();
	efx_magic_event(channel, EFX_CHANNEL_MAGIC_TEST(channel));
}