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
struct flexcop_device {void* bus_specific; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  err (char*) ; 
 int /*<<< orphan*/  kfree (struct flexcop_device*) ; 
 void* kzalloc (size_t,int /*<<< orphan*/ ) ; 

struct flexcop_device *flexcop_device_kmalloc(size_t bus_specific_len)
{
	void *bus;
	struct flexcop_device *fc = kzalloc(sizeof(struct flexcop_device),
				GFP_KERNEL);
	if (!fc) {
		err("no memory");
		return NULL;
	}

	bus = kzalloc(bus_specific_len, GFP_KERNEL);
	if (!bus) {
		err("no memory");
		kfree(fc);
		return NULL;
	}

	fc->bus_specific = bus;

	return fc;
}