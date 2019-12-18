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
struct hci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_notifier_call_chain (int /*<<< orphan*/ *,int,struct hci_dev*) ; 
 int /*<<< orphan*/  hci_notifier ; 

__attribute__((used)) static void hci_notify(struct hci_dev *hdev, int event)
{
	atomic_notifier_call_chain(&hci_notifier, event, hdev);
}