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
typedef  int /*<<< orphan*/  uint ;
struct slic_config {int FruFormat; int OEMFruFormat; int /*<<< orphan*/  NwClkCtrls; int /*<<< orphan*/  PMECapab; int /*<<< orphan*/  NetIntPin1; int /*<<< orphan*/  DramRomFn; int /*<<< orphan*/  DbgDevId; int /*<<< orphan*/  Pcistatus; int /*<<< orphan*/  MaxLat; int /*<<< orphan*/  MinGrant; TYPE_1__* macinfo; int /*<<< orphan*/  RevisionId; int /*<<< orphan*/  DeviceId; int /*<<< orphan*/  VendorId; int /*<<< orphan*/  OemFru; int /*<<< orphan*/  atk_fru; } ;
struct sliccard {int card_size; int adapters_allocated; int /*<<< orphan*/  pingstatus; int /*<<< orphan*/  gennumber; struct adapter** adapter; int /*<<< orphan*/  adapters_activated; int /*<<< orphan*/  slotnumber; int /*<<< orphan*/  busnumber; struct slic_config config; } ;
struct seq_file {struct sliccard* private; } ;
struct adapter {scalar_t__ irq; int /*<<< orphan*/  linkspeed; int /*<<< orphan*/  linkduplex; int /*<<< orphan*/  linkstate; int /*<<< orphan*/  state; int /*<<< orphan*/  physport; } ;
struct TYPE_2__ {int /*<<< orphan*/ * macaddrA; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
#define  ATK_FRU_FORMAT 132 
 int /*<<< orphan*/  GB_RCVUCODE_VERS_DATE ; 
 int /*<<< orphan*/  GB_RCVUCODE_VERS_STRING ; 
 int /*<<< orphan*/  MOJAVE_UCODE_VERS_DATE ; 
 int /*<<< orphan*/  MOJAVE_UCODE_VERS_STRING ; 
 int /*<<< orphan*/  SLIC_DUPLEX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLIC_LINKSTATE (int /*<<< orphan*/ ) ; 
 int SLIC_NBR_MACS ; 
 int /*<<< orphan*/  SLIC_RCVQ_ENTRIES ; 
 int /*<<< orphan*/  SLIC_SPEED (int /*<<< orphan*/ ) ; 
#define  VENDOR1_FRU_FORMAT 131 
#define  VENDOR2_FRU_FORMAT 130 
#define  VENDOR3_FRU_FORMAT 129 
#define  VENDOR4_FRU_FORMAT 128 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 
 int /*<<< orphan*/  seq_sprintf (struct seq_file*,char*,unsigned char,unsigned char,unsigned char,...) ; 
 int /*<<< orphan*/  slic_proc_version ; 
 int /*<<< orphan*/  slic_product_name ; 
 int /*<<< orphan*/  slic_vendor ; 

__attribute__((used)) static int slic_debug_card_show(struct seq_file *seq, void *v)
{
#ifdef MOOKTODO
	int i;
	struct sliccard *card = seq->private;
	struct slic_config *config = &card->config;
	unsigned char *fru = (unsigned char *)(&card->config.atk_fru);
	unsigned char *oemfru = (unsigned char *)(&card->config.OemFru);
#endif

	seq_printf(seq, "driver_version           : %s\n", slic_proc_version);
	seq_printf(seq, "Microcode versions:           \n");
	seq_printf(seq, "    Gigabit (gb)         : %s %s\n",
		    MOJAVE_UCODE_VERS_STRING, MOJAVE_UCODE_VERS_DATE);
	seq_printf(seq, "    Gigabit Receiver     : %s %s\n",
		    GB_RCVUCODE_VERS_STRING, GB_RCVUCODE_VERS_DATE);
	seq_printf(seq, "Vendor                   : %s\n", slic_vendor);
	seq_printf(seq, "Product Name             : %s\n", slic_product_name);
#ifdef MOOKTODO
	seq_printf(seq, "VendorId                 : %4.4X\n",
		    config->VendorId);
	seq_printf(seq, "DeviceId                 : %4.4X\n",
		    config->DeviceId);
	seq_printf(seq, "RevisionId               : %2.2x\n",
		    config->RevisionId);
	seq_printf(seq, "Bus    #                 : %d\n", card->busnumber);
	seq_printf(seq, "Device #                 : %d\n", card->slotnumber);
	seq_printf(seq, "Interfaces               : %d\n", card->card_size);
	seq_printf(seq, "     Initialized         : %d\n",
		    card->adapters_activated);
	seq_printf(seq, "     Allocated           : %d\n",
		    card->adapters_allocated);
	ASSERT(card->card_size <= SLIC_NBR_MACS);
	for (i = 0; i < card->card_size; i++) {
		seq_printf(seq,
			   "     MAC%d : %2.2X %2.2X %2.2X %2.2X %2.2X %2.2X\n",
			   i, config->macinfo[i].macaddrA[0],
			   config->macinfo[i].macaddrA[1],
			   config->macinfo[i].macaddrA[2],
			   config->macinfo[i].macaddrA[3],
			   config->macinfo[i].macaddrA[4],
			   config->macinfo[i].macaddrA[5]);
	}
	seq_printf(seq, "     IF  Init State Duplex/Speed irq\n");
	seq_printf(seq, "     -------------------------------\n");
	for (i = 0; i < card->adapters_allocated; i++) {
		struct adapter *adapter;

		adapter = card->adapter[i];
		if (adapter) {
			seq_printf(seq,
				    "     %d   %d   %s  %s  %s    0x%X\n",
				    adapter->physport, adapter->state,
				    SLIC_LINKSTATE(adapter->linkstate),
				    SLIC_DUPLEX(adapter->linkduplex),
				    SLIC_SPEED(adapter->linkspeed),
				    (uint) adapter->irq);
		}
	}
	seq_printf(seq, "Generation #             : %4.4X\n", card->gennumber);
	seq_printf(seq, "RcvQ max entries         : %4.4X\n",
		    SLIC_RCVQ_ENTRIES);
	seq_printf(seq, "Ping Status              : %8.8X\n",
		    card->pingstatus);
	seq_printf(seq, "Minimum grant            : %2.2x\n",
		    config->MinGrant);
	seq_printf(seq, "Maximum Latency          : %2.2x\n", config->MaxLat);
	seq_printf(seq, "PciStatus                : %4.4x\n",
		    config->Pcistatus);
	seq_printf(seq, "Debug Device Id          : %4.4x\n",
		    config->DbgDevId);
	seq_printf(seq, "DRAM ROM Function        : %4.4x\n",
		    config->DramRomFn);
	seq_printf(seq, "Network interface Pin 1  : %2.2x\n",
		    config->NetIntPin1);
	seq_printf(seq, "Network interface Pin 2  : %2.2x\n",
		    config->NetIntPin1);
	seq_printf(seq, "Network interface Pin 3  : %2.2x\n",
		    config->NetIntPin1);
	seq_printf(seq, "PM capabilities          : %4.4X\n",
		    config->PMECapab);
	seq_printf(seq, "Network Clock Controls   : %4.4X\n",
		    config->NwClkCtrls);

	switch (config->FruFormat) {
	case ATK_FRU_FORMAT:
		{
			seq_printf(seq,
			    "Vendor                   : Alacritech, Inc.\n");
			seq_printf(seq,
			    "Assembly #               : %c%c%c%c%c%c\n",
				    fru[0], fru[1], fru[2], fru[3], fru[4],
				    fru[5]);
			seq_printf(seq,
				    "Revision #               : %c%c\n",
				    fru[6], fru[7]);

			if (config->OEMFruFormat == VENDOR4_FRU_FORMAT) {
				seq_printf(seq,
					    "Serial   #               : "
					    "%c%c%c%c%c%c%c%c%c%c%c%c\n",
					    fru[8], fru[9], fru[10],
					    fru[11], fru[12], fru[13],
					    fru[16], fru[17], fru[18],
					    fru[19], fru[20], fru[21]);
			} else {
				seq_printf(seq,
					    "Serial   #               : "
					    "%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",
					    fru[8], fru[9], fru[10],
					    fru[11], fru[12], fru[13],
					    fru[14], fru[15], fru[16],
					    fru[17], fru[18], fru[19],
					    fru[20], fru[21]);
			}
			break;
		}

	default:
		{
			seq_printf(seq,
			    "Vendor                   : Alacritech, Inc.\n");
			seq_printf(seq,
			    "Serial   #               : Empty FRU\n");
			break;
		}
	}

	switch (config->OEMFruFormat) {
	case VENDOR1_FRU_FORMAT:
		{
			seq_printf(seq, "FRU Information:\n");
			seq_printf(seq, "    Commodity #          : %c\n",
				    oemfru[0]);
			seq_printf(seq,
				    "    Assembly #           : %c%c%c%c\n",
				    oemfru[1], oemfru[2], oemfru[3], oemfru[4]);
			seq_printf(seq,
				    "    Revision #           : %c%c\n",
				    oemfru[5], oemfru[6]);
			seq_printf(seq,
				    "    Supplier #           : %c%c\n",
				    oemfru[7], oemfru[8]);
			seq_printf(seq,
				    "    Date                 : %c%c\n",
				    oemfru[9], oemfru[10]);
			seq_sprintf(seq,
				    "    Sequence #           : %c%c%c\n",
				    oemfru[11], oemfru[12], oemfru[13]);
			break;
		}

	case VENDOR2_FRU_FORMAT:
		{
			seq_printf(seq, "FRU Information:\n");
			seq_printf(seq,
				    "    Part     #           : "
				    "%c%c%c%c%c%c%c%c\n",
				    oemfru[0], oemfru[1], oemfru[2],
				    oemfru[3], oemfru[4], oemfru[5],
				    oemfru[6], oemfru[7]);
			seq_printf(seq,
				    "    Supplier #           : %c%c%c%c%c\n",
				    oemfru[8], oemfru[9], oemfru[10],
				    oemfru[11], oemfru[12]);
			seq_printf(seq,
				    "    Date                 : %c%c%c\n",
				    oemfru[13], oemfru[14], oemfru[15]);
			seq_sprintf(seq,
				    "    Sequence #           : %c%c%c%c\n",
				    oemfru[16], oemfru[17], oemfru[18],
				    oemfru[19]);
			break;
		}

	case VENDOR3_FRU_FORMAT:
		{
			seq_printf(seq, "FRU Information:\n");
		}

	case VENDOR4_FRU_FORMAT:
		{
			seq_printf(seq, "FRU Information:\n");
			seq_printf(seq,
				    "    FRU Number           : "
				    "%c%c%c%c%c%c%c%c\n",
				    oemfru[0], oemfru[1], oemfru[2],
				    oemfru[3], oemfru[4], oemfru[5],
				    oemfru[6], oemfru[7]);
			seq_sprintf(seq,
				    "    Part Number          : "
				    "%c%c%c%c%c%c%c%c\n",
				    oemfru[8], oemfru[9], oemfru[10],
				    oemfru[11], oemfru[12], oemfru[13],
				    oemfru[14], oemfru[15]);
			seq_printf(seq,
				    "    EC Level             : "
				    "%c%c%c%c%c%c%c%c\n",
				    oemfru[16], oemfru[17], oemfru[18],
				    oemfru[19], oemfru[20], oemfru[21],
				    oemfru[22], oemfru[23]);
			break;
		}

	default:
		break;
	}
#endif

	return 0;
}