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
struct ssb_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ssb_ohci_detach (struct ssb_device*) ; 

__attribute__((used)) static void ssb_ohci_remove(struct ssb_device *dev)
{
	ssb_ohci_detach(dev);
}