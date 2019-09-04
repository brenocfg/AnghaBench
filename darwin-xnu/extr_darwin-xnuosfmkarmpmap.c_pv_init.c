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

/* Variables and functions */
 void* PV_ENTRY_NULL ; 
 int pv_free_count ; 
 void* pv_free_list ; 
 int /*<<< orphan*/  pv_free_list_lock ; 
 int pv_kern_free_count ; 
 void* pv_kern_free_list ; 
 int /*<<< orphan*/  pv_kern_free_list_lock ; 
 int /*<<< orphan*/  simple_lock_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pv_init(
	void)
{
	simple_lock_init(&pv_free_list_lock, 0);
	simple_lock_init(&pv_kern_free_list_lock, 0);
	pv_free_list = PV_ENTRY_NULL;
	pv_free_count = 0x0U;
	pv_kern_free_list = PV_ENTRY_NULL;
	pv_kern_free_count = 0x0U;
}