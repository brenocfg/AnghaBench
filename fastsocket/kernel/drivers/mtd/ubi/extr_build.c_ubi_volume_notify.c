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
struct ubi_volume {int dummy; } ;
struct ubi_notification {int /*<<< orphan*/  vi; int /*<<< orphan*/  di; } ;
struct ubi_device {int dummy; } ;

/* Variables and functions */
 int blocking_notifier_call_chain (int /*<<< orphan*/ *,int,struct ubi_notification*) ; 
 int /*<<< orphan*/  ubi_do_get_device_info (struct ubi_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubi_do_get_volume_info (struct ubi_device*,struct ubi_volume*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubi_notifiers ; 

int ubi_volume_notify(struct ubi_device *ubi, struct ubi_volume *vol, int ntype)
{
	struct ubi_notification nt;

	ubi_do_get_device_info(ubi, &nt.di);
	ubi_do_get_volume_info(ubi, vol, &nt.vi);
	return blocking_notifier_call_chain(&ubi_notifiers, ntype, &nt);
}