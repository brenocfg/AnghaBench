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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  SFI_CTL_OPERATION_SFI_GET_WINDOW ; 
 int __sfi_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int system_get_sfi_window(uint64_t *sfi_window_usec)
{
	return __sfi_ctl(SFI_CTL_OPERATION_SFI_GET_WINDOW, 0, 0, sfi_window_usec);
}