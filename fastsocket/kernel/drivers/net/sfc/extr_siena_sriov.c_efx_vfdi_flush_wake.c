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
struct efx_vf {int /*<<< orphan*/  rxq_retry_count; int /*<<< orphan*/  rxq_count; int /*<<< orphan*/  txq_count; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb () ; 

__attribute__((used)) static bool efx_vfdi_flush_wake(struct efx_vf *vf)
{
	/* Ensure that all updates are visible to efx_vfdi_fini_all_queues() */
	smp_mb();

	return (!vf->txq_count && !vf->rxq_count) ||
		atomic_read(&vf->rxq_retry_count);
}