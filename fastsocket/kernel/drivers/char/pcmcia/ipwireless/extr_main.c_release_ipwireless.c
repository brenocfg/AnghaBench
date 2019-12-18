#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  Size; int /*<<< orphan*/  Base; } ;
struct TYPE_4__ {int /*<<< orphan*/  Size; int /*<<< orphan*/  Base; } ;
struct ipw_dev {int /*<<< orphan*/  link; int /*<<< orphan*/  handle_attr_memory; scalar_t__ attr_memory; int /*<<< orphan*/  handle_common_memory; scalar_t__ common_memory; TYPE_1__ request_attr_memory; TYPE_2__ request_common_memory; } ;

/* Variables and functions */
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  pcmcia_disable_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcmcia_release_window (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void release_ipwireless(struct ipw_dev *ipw)
{
	pcmcia_disable_device(ipw->link);

	if (ipw->common_memory) {
		release_mem_region(ipw->request_common_memory.Base,
				ipw->request_common_memory.Size);
		iounmap(ipw->common_memory);
	}
	if (ipw->attr_memory) {
		release_mem_region(ipw->request_attr_memory.Base,
				ipw->request_attr_memory.Size);
		iounmap(ipw->attr_memory);
	}
	if (ipw->common_memory)
		pcmcia_release_window(ipw->handle_common_memory);
	if (ipw->attr_memory)
		pcmcia_release_window(ipw->handle_attr_memory);

	/* Break the link with Card Services */
	pcmcia_disable_device(ipw->link);
}