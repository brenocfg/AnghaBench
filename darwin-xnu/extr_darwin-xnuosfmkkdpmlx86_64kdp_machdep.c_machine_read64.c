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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  caddr_t ;
typedef  int /*<<< orphan*/  addr64_t ;

/* Variables and functions */
 int /*<<< orphan*/  kdp_machine_vm_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

unsigned
machine_read64(addr64_t srcaddr, caddr_t dstaddr, uint32_t len)
{
	return (unsigned)kdp_machine_vm_read(srcaddr, dstaddr, len);
}