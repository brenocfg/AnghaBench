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
struct wlp_neighbor_e {int /*<<< orphan*/  node; struct uwb_dev* uwb_dev; } ;
struct wlp {int /*<<< orphan*/  neighbors; } ;
struct uwb_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct wlp_neighbor_e* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uwb_dev_get (struct uwb_dev*) ; 
 int /*<<< orphan*/  wlp_neighbor_init (struct wlp_neighbor_e*) ; 

__attribute__((used)) static
int wlp_add_neighbor(struct wlp *wlp, struct uwb_dev *dev)
{
	int result = 0;
	int discoverable;
	struct wlp_neighbor_e *neighbor;

	/*
	 * FIXME:
	 * Use contents of WLP IE found in beacon cache to determine if
	 * neighbor is discoverable.
	 * The device does not support WLP IE yet so this still needs to be
	 * done. Until then we assume all devices are discoverable.
	 */
	discoverable = 1; /* will be changed when FIXME disappears */
	if (discoverable) {
		/* Add neighbor to cache for discovery */
		neighbor = kzalloc(sizeof(*neighbor), GFP_KERNEL);
		if (neighbor == NULL) {
			dev_err(&dev->dev, "Unable to create memory for "
				"new neighbor. \n");
			result = -ENOMEM;
			goto error_no_mem;
		}
		wlp_neighbor_init(neighbor);
		uwb_dev_get(dev);
		neighbor->uwb_dev = dev;
		list_add(&neighbor->node, &wlp->neighbors);
	}
error_no_mem:
	return result;
}