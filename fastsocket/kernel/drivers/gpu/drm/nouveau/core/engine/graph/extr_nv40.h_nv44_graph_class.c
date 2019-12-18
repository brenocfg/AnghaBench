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
struct nouveau_device {int chipset; } ;

/* Variables and functions */
 struct nouveau_device* nv_device (void*) ; 

__attribute__((used)) static inline int
nv44_graph_class(void *priv)
{
	struct nouveau_device *device = nv_device(priv);

	if ((device->chipset & 0xf0) == 0x60)
		return 1;

	return !(0x0baf & (1 << (device->chipset & 0x0f)));
}