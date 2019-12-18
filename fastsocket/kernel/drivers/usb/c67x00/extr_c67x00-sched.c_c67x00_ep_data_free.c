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
struct usb_host_endpoint {struct c67x00_ep_data* hcpriv; } ;
struct c67x00_ep_data {int /*<<< orphan*/  node; int /*<<< orphan*/  queue; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  kfree (struct c67x00_ep_data*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_put_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int c67x00_ep_data_free(struct usb_host_endpoint *hep)
{
	struct c67x00_ep_data *ep_data = hep->hcpriv;

	if (!ep_data)
		return 0;

	if (!list_empty(&ep_data->queue))
		return -EBUSY;

	usb_put_dev(ep_data->dev);
	list_del(&ep_data->queue);
	list_del(&ep_data->node);

	kfree(ep_data);
	hep->hcpriv = NULL;

	return 0;
}