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
struct ecc_event {scalar_t__ count; } ;
typedef  int /*<<< orphan*/  spl_t ;
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 size_t ECC_EVENT_BUFFER_COUNT ; 
 scalar_t__ ECC_EVENT_INFO_DATA_ENTRIES ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  bcopy (struct ecc_event const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ecc_correction_count ; 
 int /*<<< orphan*/ * ecc_data ; 
 scalar_t__ ecc_data_empty ; 
 int /*<<< orphan*/  ecc_data_lock ; 
 size_t ecc_data_next_read ; 
 size_t ecc_data_next_write ; 
 int /*<<< orphan*/  lck_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*,unsigned int) ; 
 int /*<<< orphan*/  splhigh () ; 
 int /*<<< orphan*/  splx (int /*<<< orphan*/ ) ; 

kern_return_t
ecc_log_record_event(const struct ecc_event *ev)
{
	spl_t x;

	if (ev->count > ECC_EVENT_INFO_DATA_ENTRIES) {
		panic("Count of %u on ecc event is too large.", (unsigned)ev->count);
	}

	x = splhigh();
	lck_spin_lock(&ecc_data_lock);

	ecc_correction_count++;

	if (ecc_data_next_read == ecc_data_next_write && !ecc_data_empty)  {
		lck_spin_unlock(&ecc_data_lock);
		splx(x);
		return KERN_FAILURE;
	}

	bcopy(ev, &ecc_data[ecc_data_next_write], sizeof(*ev));
	ecc_data_next_write++;
	ecc_data_next_write %= ECC_EVENT_BUFFER_COUNT;
	ecc_data_empty = FALSE;

	lck_spin_unlock(&ecc_data_lock);
	splx(x);

	return KERN_SUCCESS;
}