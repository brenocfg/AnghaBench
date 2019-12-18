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
struct rxf_desc {int /*<<< orphan*/  len; int /*<<< orphan*/  pa_hi; int /*<<< orphan*/  pa_lo; int /*<<< orphan*/  va_lo; int /*<<< orphan*/  info; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void print_rxfd(struct rxf_desc *rxfd)
{
	DBG("=== RxF desc CHIP ORDER/ENDIANESS =============\n"
	    "info 0x%x va_lo %u pa_lo 0x%x pa_hi 0x%x len 0x%x\n",
	    rxfd->info, rxfd->va_lo, rxfd->pa_lo, rxfd->pa_hi, rxfd->len);
}