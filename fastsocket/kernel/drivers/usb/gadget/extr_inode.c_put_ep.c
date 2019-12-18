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
struct ep_data {int /*<<< orphan*/  wait; int /*<<< orphan*/  epfiles; int /*<<< orphan*/  dev; int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ep_data*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_dev (int /*<<< orphan*/ ) ; 
 int waitqueue_active (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void put_ep (struct ep_data *data)
{
	if (likely (!atomic_dec_and_test (&data->count)))
		return;
	put_dev (data->dev);
	/* needs no more cleanup */
	BUG_ON (!list_empty (&data->epfiles));
	BUG_ON (waitqueue_active (&data->wait));
	kfree (data);
}