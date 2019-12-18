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
struct hso_shared_int {int /*<<< orphan*/  shared_int_lock; struct hso_shared_int* shared_intr_buf; int /*<<< orphan*/  shared_intr_urb; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct hso_shared_int*) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hso_free_shared_int(struct hso_shared_int *mux)
{
	usb_free_urb(mux->shared_intr_urb);
	kfree(mux->shared_intr_buf);
	mutex_unlock(&mux->shared_int_lock);
	kfree(mux);
}