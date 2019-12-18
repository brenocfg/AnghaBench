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
typedef  int /*<<< orphan*/  sle64 ;

/* Variables and functions */
 int /*<<< orphan*/  current_kernel_time () ; 
 int /*<<< orphan*/  utc2ntfs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline sle64 get_current_ntfs_time(void)
{
	return utc2ntfs(current_kernel_time());
}