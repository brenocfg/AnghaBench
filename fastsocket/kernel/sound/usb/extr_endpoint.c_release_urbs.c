#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_usb_endpoint {int nurbs; int /*<<< orphan*/ * syncbuf; int /*<<< orphan*/  sync_dma; TYPE_1__* chip; int /*<<< orphan*/ * urb; int /*<<< orphan*/ * prepare_data_urb; int /*<<< orphan*/ * retire_data_urb; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int SYNC_URBS ; 
 int /*<<< orphan*/  deactivate_urbs (struct snd_usb_endpoint*,int,int) ; 
 int /*<<< orphan*/  release_urb_ctx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_buffer_free (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_clear_urbs (struct snd_usb_endpoint*) ; 

__attribute__((used)) static void release_urbs(struct snd_usb_endpoint *ep, int force)
{
	int i;

	/* route incoming urbs to nirvana */
	ep->retire_data_urb = NULL;
	ep->prepare_data_urb = NULL;

	/* stop urbs */
	deactivate_urbs(ep, force, 1);
	wait_clear_urbs(ep);

	for (i = 0; i < ep->nurbs; i++)
		release_urb_ctx(&ep->urb[i]);

	if (ep->syncbuf)
		usb_buffer_free(ep->chip->dev, SYNC_URBS * 4,
				  ep->syncbuf, ep->sync_dma);

	ep->syncbuf = NULL;
	ep->nurbs = 0;
}