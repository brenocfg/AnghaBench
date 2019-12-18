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
struct ilo_hwinfo {int /*<<< orphan*/ * mmio_vaddr; } ;

/* Variables and functions */
 size_t DB_OUT ; 
 int ioread32 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int get_device_outbound(struct ilo_hwinfo *hw)
{
	return ioread32(&hw->mmio_vaddr[DB_OUT]);
}