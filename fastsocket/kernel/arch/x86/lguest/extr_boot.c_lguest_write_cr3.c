#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned long pgdir; } ;

/* Variables and functions */
 int /*<<< orphan*/  LHCALL_NEW_PGTABLE ; 
 int cr3_changed ; 
 int /*<<< orphan*/  lazy_hcall1 (int /*<<< orphan*/ ,unsigned long) ; 
 TYPE_1__ lguest_data ; 

__attribute__((used)) static void lguest_write_cr3(unsigned long cr3)
{
	lguest_data.pgdir = cr3;
	lazy_hcall1(LHCALL_NEW_PGTABLE, cr3);
	cr3_changed = true;
}