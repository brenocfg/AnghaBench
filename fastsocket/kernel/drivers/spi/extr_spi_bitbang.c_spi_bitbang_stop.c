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
struct spi_bitbang {int /*<<< orphan*/  workqueue; int /*<<< orphan*/  queue; int /*<<< orphan*/  master; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_unregister_master (int /*<<< orphan*/ ) ; 

int spi_bitbang_stop(struct spi_bitbang *bitbang)
{
	spi_unregister_master(bitbang->master);

	WARN_ON(!list_empty(&bitbang->queue));

	destroy_workqueue(bitbang->workqueue);

	return 0;
}