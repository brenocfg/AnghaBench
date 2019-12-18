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
struct ni_65xx_subdevice_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct ni_65xx_subdevice_private* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ni_65xx_subdevice_private *ni_65xx_alloc_subdevice_private(void)
{
	struct ni_65xx_subdevice_private *subdev_private =
	    kzalloc(sizeof(struct ni_65xx_subdevice_private), GFP_KERNEL);
	if (subdev_private == NULL)
		return NULL;
	return subdev_private;
}