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
typedef  int /*<<< orphan*/  vme_width_t ;
typedef  int /*<<< orphan*/  vme_cycle_t ;
typedef  int /*<<< orphan*/  vme_address_t ;
struct vme_master_resource {int kern_base; int /*<<< orphan*/  lock; } ;
struct vme_bus_error {int address; } ;
typedef  int ssize_t ;
typedef  int loff_t ;
struct TYPE_2__ {scalar_t__ kern_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  __tsi148_master_get (struct vme_master_resource*,int*,unsigned long long*,unsigned long long*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  err_chk ; 
 TYPE_1__* flush_image ; 
 int /*<<< orphan*/  ioread16 (scalar_t__) ; 
 int /*<<< orphan*/  memcpy_toio (int,void*,unsigned int) ; 
 int /*<<< orphan*/  printk (char*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsi148_clear_errors (int /*<<< orphan*/ ,int,size_t) ; 
 struct vme_bus_error* tsi148_find_error (int /*<<< orphan*/ ,int,size_t) ; 

ssize_t tsi148_master_write(struct vme_master_resource *image, void *buf,
	size_t count, loff_t offset)
{
	int retval = 0, enabled;
	unsigned long long vme_base, size;
	vme_address_t aspace;
	vme_cycle_t cycle;
	vme_width_t dwidth;

	struct vme_bus_error *vme_err = NULL;

	spin_lock(&(image->lock));

	memcpy_toio(image->kern_base + offset, buf, (unsigned int)count);
	retval = count;

	/*
	 * Writes are posted. We need to do a read on the VME bus to flush out
	 * all of the writes before we check for errors. We can't guarentee
	 * that reading the data we have just written is safe. It is believed
	 * that there isn't any read, write re-ordering, so we can read any
	 * location in VME space, so lets read the Device ID from the tsi148's
	 * own registers as mapped into CR/CSR space.
	 *
	 * We check for saved errors in the written address range/space.
	 */

	if (!err_chk)
		goto skip_chk;

	/*
	 * Get window info first, to maximise the time that the buffers may
	 * fluch on their own
	 */
	__tsi148_master_get(image, &enabled, &vme_base, &size, &aspace, &cycle,
		&dwidth);

	ioread16(flush_image->kern_base + 0x7F000);

	vme_err = tsi148_find_error(aspace, vme_base + offset, count);
	if(vme_err != NULL) {
		printk("First VME write error detected an at address 0x%llx\n",
			vme_err->address);
		retval = vme_err->address - (vme_base + offset);
		/* Clear down save errors in this address range */
		tsi148_clear_errors(aspace, vme_base + offset, count);
	}

skip_chk:
	spin_unlock(&(image->lock));

	return retval;
}