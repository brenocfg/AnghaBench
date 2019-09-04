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
struct ecc_event {int dummy; } ;
typedef  int /*<<< orphan*/  spl_t ;
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 size_t ECC_EVENT_BUFFER_COUNT ; 
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,struct ecc_event*,int) ; 
 int /*<<< orphan*/ * ecc_data ; 
 scalar_t__ ecc_data_empty ; 
 int /*<<< orphan*/  ecc_data_lock ; 
 size_t ecc_data_next_read ; 
 size_t ecc_data_next_write ; 
 int /*<<< orphan*/  lck_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  splhigh () ; 
 int /*<<< orphan*/  splx (int /*<<< orphan*/ ) ; 

kern_return_t
ecc_log_get_next_event(struct ecc_event *ev)
{
	spl_t x;

	x = splhigh();
	lck_spin_lock(&ecc_data_lock);

	if (ecc_data_empty)  {
		assert(ecc_data_next_write == ecc_data_next_read);

		lck_spin_unlock(&ecc_data_lock);
		splx(x);
		return KERN_FAILURE;
	}

	bcopy(&ecc_data[ecc_data_next_read], ev, sizeof(*ev));
	ecc_data_next_read++;
	ecc_data_next_read %= ECC_EVENT_BUFFER_COUNT;

	if (ecc_data_next_read == ecc_data_next_write) {
		ecc_data_empty = TRUE;
	}

	lck_spin_unlock(&ecc_data_lock);
	splx(x);

	return KERN_SUCCESS;
}