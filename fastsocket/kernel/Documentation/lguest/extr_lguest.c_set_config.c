#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct device {TYPE_1__* desc; } ;
struct TYPE_4__ {unsigned int descpage; } ;
struct TYPE_3__ {unsigned int config_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 unsigned int device_config (struct device*) ; 
 TYPE_2__ devices ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 unsigned int getpagesize () ; 
 int /*<<< orphan*/  memcpy (unsigned int,void const*,unsigned int) ; 

__attribute__((used)) static void set_config(struct device *dev, unsigned len, const void *conf)
{
	/* Check we haven't overflowed our single page. */
	if (device_config(dev) + len > devices.descpage + getpagesize())
		errx(1, "Too many devices");

	/* Copy in the config information, and store the length. */
	memcpy(device_config(dev), conf, len);
	dev->desc->config_len = len;

	/* Size must fit in config_len field (8 bits)! */
	assert(dev->desc->config_len == len);
}