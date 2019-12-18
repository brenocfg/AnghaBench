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
struct efx_vf {int /*<<< orphan*/  rxq_retry_count; int /*<<< orphan*/  rxq_retry_mask; scalar_t__ rxq_count; int /*<<< orphan*/  rxq_mask; scalar_t__ txq_count; int /*<<< orphan*/  txq_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void efx_vfdi_flush_clear(struct efx_vf *vf)
{
	memset(vf->txq_mask, 0, sizeof(vf->txq_mask));
	vf->txq_count = 0;
	memset(vf->rxq_mask, 0, sizeof(vf->rxq_mask));
	vf->rxq_count = 0;
	memset(vf->rxq_retry_mask, 0, sizeof(vf->rxq_retry_mask));
	atomic_set(&vf->rxq_retry_count, 0);
}