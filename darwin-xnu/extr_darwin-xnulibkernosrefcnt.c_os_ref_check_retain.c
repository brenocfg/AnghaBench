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
struct os_refcnt {int dummy; } ;
typedef  int /*<<< orphan*/  os_ref_count_t ;

/* Variables and functions */
 int /*<<< orphan*/  os_ref_assert_referenced (struct os_refcnt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_ref_check_overflow (struct os_refcnt*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
os_ref_check_retain(struct os_refcnt *rc, os_ref_count_t count)
{
	os_ref_assert_referenced(rc, count);
	os_ref_check_overflow(rc, count);
}