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
struct snd_usb_substream {int /*<<< orphan*/  data_endpoint; int /*<<< orphan*/  sync_endpoint; } ;

/* Variables and functions */
 int snd_usb_endpoint_deactivate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int deactivate_endpoints(struct snd_usb_substream *subs)
{
	int reta, retb;

	reta = snd_usb_endpoint_deactivate(subs->sync_endpoint);
	retb = snd_usb_endpoint_deactivate(subs->data_endpoint);

	if (reta < 0)
		return reta;

	if (retb < 0)
		return retb;

	return 0;
}