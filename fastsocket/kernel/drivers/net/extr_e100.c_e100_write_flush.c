#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nic {TYPE_2__* csr; } ;
struct TYPE_3__ {int /*<<< orphan*/  status; } ;
struct TYPE_4__ {TYPE_1__ scb; } ;

/* Variables and functions */
 int /*<<< orphan*/  ioread8 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void e100_write_flush(struct nic *nic)
{
	/* Flush previous PCI writes through intermediate bridges
	 * by doing a benign read */
	(void)ioread8(&nic->csr->scb.status);
}