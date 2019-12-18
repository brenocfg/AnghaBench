#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct seq_file {scalar_t__ private; } ;
struct TYPE_10__ {scalar_t__ virt; } ;
struct i2o_controller {TYPE_1__ hrt; } ;
struct TYPE_18__ {int num_entries; int entry_len; TYPE_8__* hrt_entry; scalar_t__ hrt_version; } ;
typedef  TYPE_9__ i2o_hrt ;
struct TYPE_15__ {int /*<<< orphan*/  PciDeviceID; int /*<<< orphan*/  PciVendorID; int /*<<< orphan*/  PciFunctionNumber; int /*<<< orphan*/  PciDeviceNumber; int /*<<< orphan*/  PciBusNumber; } ;
struct TYPE_14__ {int /*<<< orphan*/  McaSlotNumber; int /*<<< orphan*/  McaBaseMemoryAddress; int /*<<< orphan*/  McaBaseIOPort; } ;
struct TYPE_13__ {int /*<<< orphan*/  EisaSlotNumber; int /*<<< orphan*/  EisaBaseMemoryAddress; int /*<<< orphan*/  EisaBaseIOPort; } ;
struct TYPE_12__ {int /*<<< orphan*/  CSN; int /*<<< orphan*/  IsaBaseMemoryAddress; int /*<<< orphan*/  IsaBaseIOPort; } ;
struct TYPE_11__ {int /*<<< orphan*/  LbBaseMemoryAddress; int /*<<< orphan*/  LbBaseIOPort; } ;
struct TYPE_16__ {TYPE_6__ pci_bus; TYPE_5__ mca_bus; TYPE_4__ eisa_bus; TYPE_3__ isa_bus; TYPE_2__ local_bus; } ;
struct TYPE_17__ {int bus_type; TYPE_7__ bus; int /*<<< orphan*/  parent_tid; int /*<<< orphan*/  adapter_id; } ;

/* Variables and functions */
#define  I2O_BUS_EISA 132 
#define  I2O_BUS_ISA 131 
#define  I2O_BUS_LOCAL 130 
#define  I2O_BUS_MCA 129 
#define  I2O_BUS_PCI 128 
 int /*<<< orphan*/ * bus_strings ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 

__attribute__((used)) static int i2o_seq_show_hrt(struct seq_file *seq, void *v)
{
	struct i2o_controller *c = (struct i2o_controller *)seq->private;
	i2o_hrt *hrt = (i2o_hrt *) c->hrt.virt;
	u32 bus;
	int i;

	if (hrt->hrt_version) {
		seq_printf(seq,
			   "HRT table for controller is too new a version.\n");
		return 0;
	}

	seq_printf(seq, "HRT has %d entries of %d bytes each.\n",
		   hrt->num_entries, hrt->entry_len << 2);

	for (i = 0; i < hrt->num_entries; i++) {
		seq_printf(seq, "Entry %d:\n", i);
		seq_printf(seq, "   Adapter ID: %0#10x\n",
			   hrt->hrt_entry[i].adapter_id);
		seq_printf(seq, "   Controlling tid: %0#6x\n",
			   hrt->hrt_entry[i].parent_tid);

		if (hrt->hrt_entry[i].bus_type != 0x80) {
			bus = hrt->hrt_entry[i].bus_type;
			seq_printf(seq, "   %s Information\n",
				   bus_strings[bus]);

			switch (bus) {
			case I2O_BUS_LOCAL:
				seq_printf(seq, "     IOBase: %0#6x,",
					   hrt->hrt_entry[i].bus.local_bus.
					   LbBaseIOPort);
				seq_printf(seq, " MemoryBase: %0#10x\n",
					   hrt->hrt_entry[i].bus.local_bus.
					   LbBaseMemoryAddress);
				break;

			case I2O_BUS_ISA:
				seq_printf(seq, "     IOBase: %0#6x,",
					   hrt->hrt_entry[i].bus.isa_bus.
					   IsaBaseIOPort);
				seq_printf(seq, " MemoryBase: %0#10x,",
					   hrt->hrt_entry[i].bus.isa_bus.
					   IsaBaseMemoryAddress);
				seq_printf(seq, " CSN: %0#4x,",
					   hrt->hrt_entry[i].bus.isa_bus.CSN);
				break;

			case I2O_BUS_EISA:
				seq_printf(seq, "     IOBase: %0#6x,",
					   hrt->hrt_entry[i].bus.eisa_bus.
					   EisaBaseIOPort);
				seq_printf(seq, " MemoryBase: %0#10x,",
					   hrt->hrt_entry[i].bus.eisa_bus.
					   EisaBaseMemoryAddress);
				seq_printf(seq, " Slot: %0#4x,",
					   hrt->hrt_entry[i].bus.eisa_bus.
					   EisaSlotNumber);
				break;

			case I2O_BUS_MCA:
				seq_printf(seq, "     IOBase: %0#6x,",
					   hrt->hrt_entry[i].bus.mca_bus.
					   McaBaseIOPort);
				seq_printf(seq, " MemoryBase: %0#10x,",
					   hrt->hrt_entry[i].bus.mca_bus.
					   McaBaseMemoryAddress);
				seq_printf(seq, " Slot: %0#4x,",
					   hrt->hrt_entry[i].bus.mca_bus.
					   McaSlotNumber);
				break;

			case I2O_BUS_PCI:
				seq_printf(seq, "     Bus: %0#4x",
					   hrt->hrt_entry[i].bus.pci_bus.
					   PciBusNumber);
				seq_printf(seq, " Dev: %0#4x",
					   hrt->hrt_entry[i].bus.pci_bus.
					   PciDeviceNumber);
				seq_printf(seq, " Func: %0#4x",
					   hrt->hrt_entry[i].bus.pci_bus.
					   PciFunctionNumber);
				seq_printf(seq, " Vendor: %0#6x",
					   hrt->hrt_entry[i].bus.pci_bus.
					   PciVendorID);
				seq_printf(seq, " Device: %0#6x\n",
					   hrt->hrt_entry[i].bus.pci_bus.
					   PciDeviceID);
				break;

			default:
				seq_printf(seq, "      Unsupported Bus Type\n");
			}
		} else
			seq_printf(seq, "   Unknown Bus Type\n");
	}

	return 0;
}