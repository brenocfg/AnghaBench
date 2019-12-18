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
struct of_device_id {int dummy; } ;
struct of_device {int /*<<< orphan*/  node; } ;

/* Variables and functions */
 struct of_device_id const* of_match_node (struct of_device_id const*,int /*<<< orphan*/ ) ; 

const struct of_device_id *of_match_device(const struct of_device_id *matches,
					const struct of_device *dev)
{
	if (!dev->node)
		return NULL;
	return of_match_node(matches, dev->node);
}