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
struct snd_usb_substream {int /*<<< orphan*/  data_endpoint; int /*<<< orphan*/  flags; int /*<<< orphan*/  sync_endpoint; } ;

/* Variables and functions */
 int /*<<< orphan*/  SUBSTREAM_FLAG_DATA_EP_STARTED ; 
 int /*<<< orphan*/  SUBSTREAM_FLAG_SYNC_EP_STARTED ; 
 int /*<<< orphan*/  snd_usb_endpoint_stop (int /*<<< orphan*/ ,int,int,int) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void stop_endpoints(struct snd_usb_substream *subs,
			   int force, int can_sleep, int wait)
{
	if (test_and_clear_bit(SUBSTREAM_FLAG_SYNC_EP_STARTED, &subs->flags))
		snd_usb_endpoint_stop(subs->sync_endpoint,
				      force, can_sleep, wait);

	if (test_and_clear_bit(SUBSTREAM_FLAG_DATA_EP_STARTED, &subs->flags))
		snd_usb_endpoint_stop(subs->data_endpoint,
				      force, can_sleep, wait);
}