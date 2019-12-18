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
struct rtc_wkalrm {int /*<<< orphan*/  time; int /*<<< orphan*/  pending; int /*<<< orphan*/  enabled; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  efi_time_t ;
typedef  scalar_t__ efi_status_t ;
typedef  int /*<<< orphan*/  efi_bool_t ;
struct TYPE_2__ {scalar_t__ (* get_wakeup_time ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 scalar_t__ EFI_SUCCESS ; 
 int EINVAL ; 
 int /*<<< orphan*/  convert_from_efi_time (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__ efi ; 
 int rtc_valid_tm (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int efi_read_alarm(struct device *dev, struct rtc_wkalrm *wkalrm)
{
	efi_time_t eft;
	efi_status_t status;

	/*
	 * As of EFI v1.10, this call always returns an unsupported status
	 */
	status = efi.get_wakeup_time((efi_bool_t *)&wkalrm->enabled,
				     (efi_bool_t *)&wkalrm->pending, &eft);

	if (status != EFI_SUCCESS)
		return -EINVAL;

	convert_from_efi_time(&eft, &wkalrm->time);

	return rtc_valid_tm(&wkalrm->time);
}