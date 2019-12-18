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
struct wbsd_host {scalar_t__ num_sg; int /*<<< orphan*/  lock; int /*<<< orphan*/  finish_tasklet; int /*<<< orphan*/  mrq; } ;
struct mmc_data {int flags; } ;

/* Variables and functions */
 int MMC_DATA_WRITE ; 
 int /*<<< orphan*/  WBSD_IDX_FIFOEN ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wbsd_empty_fifo (struct wbsd_host*) ; 
 int /*<<< orphan*/  wbsd_fill_fifo (struct wbsd_host*) ; 
 struct mmc_data* wbsd_get_data (struct wbsd_host*) ; 
 int /*<<< orphan*/  wbsd_write_index (struct wbsd_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wbsd_tasklet_fifo(unsigned long param)
{
	struct wbsd_host *host = (struct wbsd_host *)param;
	struct mmc_data *data;

	spin_lock(&host->lock);

	if (!host->mrq)
		goto end;

	data = wbsd_get_data(host);
	if (!data)
		goto end;

	if (data->flags & MMC_DATA_WRITE)
		wbsd_fill_fifo(host);
	else
		wbsd_empty_fifo(host);

	/*
	 * Done?
	 */
	if (host->num_sg == 0) {
		wbsd_write_index(host, WBSD_IDX_FIFOEN, 0);
		tasklet_schedule(&host->finish_tasklet);
	}

end:
	spin_unlock(&host->lock);
}