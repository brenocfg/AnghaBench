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
struct tmio_mmc_host {int /*<<< orphan*/  sg_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  KM_BIO_SRC_IRQ ; 
 int /*<<< orphan*/  kunmap_atomic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  sg_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void tmio_mmc_kunmap_atomic(struct tmio_mmc_host *host,
	unsigned long *flags)
{
	kunmap_atomic(sg_page(host->sg_ptr), KM_BIO_SRC_IRQ);
	local_irq_restore(*flags);
}