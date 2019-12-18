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
struct mmc_data {int flags; int bytes_xfered; int blksz; int blocks; } ;
struct cb710_slot {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CB710_MMC_S1_DATA_TRANSFER_DONE ; 
 int MMC_DATA_READ ; 
 int cb710_mmc_receive (struct cb710_slot*,struct mmc_data*) ; 
 int cb710_mmc_send (struct cb710_slot*,struct mmc_data*) ; 
 int cb710_wait_for_event (struct cb710_slot*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cb710_mmc_transfer_data(struct cb710_slot *slot,
	struct mmc_data *data)
{
	int error, to;

	if (data->flags & MMC_DATA_READ)
		error = cb710_mmc_receive(slot, data);
	else
		error = cb710_mmc_send(slot, data);

	to = cb710_wait_for_event(slot, CB710_MMC_S1_DATA_TRANSFER_DONE);
	if (!error)
		error = to;

	if (!error)
		data->bytes_xfered = data->blksz * data->blocks;
	return error;
}