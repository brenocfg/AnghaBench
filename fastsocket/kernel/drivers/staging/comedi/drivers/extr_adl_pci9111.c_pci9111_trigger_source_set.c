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
struct comedi_device {int dummy; } ;
typedef  enum pci9111_trigger_sources { ____Placeholder_pci9111_trigger_sources } pci9111_trigger_sources ;

/* Variables and functions */
 int PCI9111_EITS_EXTERNAL ; 
 int PCI9111_EITS_INTERNAL ; 
 int PCI9111_TPST_SOFTWARE_TRIGGER ; 
 int PCI9111_TPST_TIMER_PACER ; 
#define  external 130 
 int pci9111_trigger_and_autoscan_get () ; 
 int /*<<< orphan*/  pci9111_trigger_and_autoscan_set (int) ; 
#define  software 129 
#define  timer_pacer 128 

__attribute__((used)) static void pci9111_trigger_source_set(struct comedi_device *dev,
				       enum pci9111_trigger_sources source)
{
	int flags;

	flags = pci9111_trigger_and_autoscan_get() & 0x09;

	switch (source) {
	case software:
		flags |= PCI9111_EITS_INTERNAL | PCI9111_TPST_SOFTWARE_TRIGGER;
		break;

	case timer_pacer:
		flags |= PCI9111_EITS_INTERNAL | PCI9111_TPST_TIMER_PACER;
		break;

	case external:
		flags |= PCI9111_EITS_EXTERNAL;
		break;
	}

	pci9111_trigger_and_autoscan_set(flags);
}