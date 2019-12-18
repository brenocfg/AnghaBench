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
struct virtio_device_id {scalar_t__ device; scalar_t__ vendor; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD (char*,char*,int,scalar_t__) ; 
 void* TO_NATIVE (scalar_t__) ; 
 scalar_t__ VIRTIO_DEV_ANY_ID ; 
 int /*<<< orphan*/  add_wildcard (char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static int do_virtio_entry(const char *filename, struct virtio_device_id *id,
			   char *alias)
{
	id->device = TO_NATIVE(id->device);
	id->vendor = TO_NATIVE(id->vendor);

	strcpy(alias, "virtio:");
	ADD(alias, "d", id->device != VIRTIO_DEV_ANY_ID, id->device);
	ADD(alias, "v", id->vendor != VIRTIO_DEV_ANY_ID, id->vendor);

	add_wildcard(alias);
	return 1;
}