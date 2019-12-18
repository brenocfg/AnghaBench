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
typedef  int /*<<< orphan*/  u32 ;
struct fritzcard {int type; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
#define  AVM_FRITZ_PCI 129 
#define  AVM_FRITZ_PCIV2 128 
 int /*<<< orphan*/  __read_status_pci (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __read_status_pciv2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32
read_status(struct fritzcard *fc, u32 channel)
{
	switch (fc->type) {
	case AVM_FRITZ_PCIV2:
		return __read_status_pciv2(fc->addr, channel);
	case AVM_FRITZ_PCI:
		return __read_status_pci(fc->addr, channel);
	}
	/* dummy */
	return 0;
}