#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int dummy; } ;
struct get_conf {size_t IRQ; int* scsi_id; scalar_t__ SECOND; int /*<<< orphan*/  MORE_support; scalar_t__ is_EISA; scalar_t__ is_PCI; int /*<<< orphan*/  len; int /*<<< orphan*/  queuesiz; int /*<<< orphan*/  IRQ_TR; int /*<<< orphan*/  cppadlen; int /*<<< orphan*/  cplen; scalar_t__ DMA_support; } ;
struct eata_ccb {int dummy; } ;
struct Scsi_Host {long unique_id; long base; long io_port; int n_io_port; size_t irq; int this_id; int can_queue; int cmd_per_lun; int max_id; int max_lun; int /*<<< orphan*/  sg_tablesize; int /*<<< orphan*/  dma_channel; } ;
struct TYPE_3__ {char* revision; char EATA_revision; unsigned long cplen; unsigned short cppadlen; int hostid; int devflags; int primary; struct Scsi_Host* next; struct Scsi_Host* prev; int /*<<< orphan*/  pdev; scalar_t__ channel; int /*<<< orphan*/  moresupport; void* bustype; int /*<<< orphan*/  name; int /*<<< orphan*/  vendor; int /*<<< orphan*/  reads; int /*<<< orphan*/  ccb; } ;
typedef  TYPE_1__ hostdata ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOW_DMA_BOARDS ; 
 int /*<<< orphan*/  DBG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBG_REGISTER ; 
 int /*<<< orphan*/  IRQF_DISABLED ; 
 void* IS_EISA ; 
 void* IS_ISA ; 
 void* IS_PCI ; 
 int /*<<< orphan*/  PIO ; 
 TYPE_1__* SD (struct Scsi_Host*) ; 
 int /*<<< orphan*/  SG_ALL ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_eata_pio_int_handler ; 
 int /*<<< orphan*/  driver_template ; 
 struct Scsi_Host* first_HBA ; 
 char* get_pio_board_data (long,size_t,int,unsigned long,unsigned short) ; 
 struct Scsi_Host* last_HBA ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_dev_get (struct pci_dev*) ; 
 int /*<<< orphan*/  print_pio_config (struct get_conf*) ; 
 int /*<<< orphan*/  print_selftest (long) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/ * reg_IRQ ; 
 int* reg_IRQL ; 
 int /*<<< orphan*/  registered_HBAs ; 
 int /*<<< orphan*/  request_irq (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct Scsi_Host*) ; 
 struct Scsi_Host* scsi_register (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int register_pio_HBA(long base, struct get_conf *gc, struct pci_dev *pdev)
{
	unsigned long size = 0;
	char *buff;
	unsigned long cplen;
	unsigned short cppadlen;
	struct Scsi_Host *sh;
	hostdata *hd;

	DBG(DBG_REGISTER, print_pio_config(gc));

	if (gc->DMA_support) {
		printk("HBA at %#.4lx supports DMA. Please use EATA-DMA driver.\n", base);
		if (!ALLOW_DMA_BOARDS)
			return 0;
	}

	if ((buff = get_pio_board_data(base, gc->IRQ, gc->scsi_id[3], cplen = (cpu_to_be32(gc->cplen) + 1) / 2, cppadlen = (cpu_to_be16(gc->cppadlen) + 1) / 2)) == NULL) {
		printk("HBA at %#lx didn't react on INQUIRY. Sorry.\n", base);
		return 0;
	}

	if (!print_selftest(base) && !ALLOW_DMA_BOARDS) {
		printk("HBA at %#lx failed while performing self test & setup.\n", base);
		return 0;
	}

	size = sizeof(hostdata) + (sizeof(struct eata_ccb) * be16_to_cpu(gc->queuesiz));

	sh = scsi_register(&driver_template, size);
	if (sh == NULL)
		return 0;

	if (!reg_IRQ[gc->IRQ]) {	/* Interrupt already registered ? */
		if (!request_irq(gc->IRQ, do_eata_pio_int_handler, IRQF_DISABLED, "EATA-PIO", sh)) {
			reg_IRQ[gc->IRQ]++;
			if (!gc->IRQ_TR)
				reg_IRQL[gc->IRQ] = 1;	/* IRQ is edge triggered */
		} else {
			printk("Couldn't allocate IRQ %d, Sorry.\n", gc->IRQ);
			return 0;
		}
	} else {		/* More than one HBA on this IRQ */
		if (reg_IRQL[gc->IRQ]) {
			printk("Can't support more than one HBA on this IRQ,\n" "  if the IRQ is edge triggered. Sorry.\n");
			return 0;
		} else
			reg_IRQ[gc->IRQ]++;
	}

	hd = SD(sh);

	memset(hd->ccb, 0, (sizeof(struct eata_ccb) * be16_to_cpu(gc->queuesiz)));
	memset(hd->reads, 0, sizeof(hd->reads));

	strlcpy(SD(sh)->vendor, &buff[8], sizeof(SD(sh)->vendor));
	strlcpy(SD(sh)->name, &buff[16], sizeof(SD(sh)->name));
	SD(sh)->revision[0] = buff[32];
	SD(sh)->revision[1] = buff[33];
	SD(sh)->revision[2] = buff[34];
	SD(sh)->revision[3] = '.';
	SD(sh)->revision[4] = buff[35];
	SD(sh)->revision[5] = 0;

	switch (be32_to_cpu(gc->len)) {
	case 0x1c:
		SD(sh)->EATA_revision = 'a';
		break;
	case 0x1e:
		SD(sh)->EATA_revision = 'b';
		break;
	case 0x22:
		SD(sh)->EATA_revision = 'c';
		break;
	case 0x24:
		SD(sh)->EATA_revision = 'z';
	default:
		SD(sh)->EATA_revision = '?';
	}

	if (be32_to_cpu(gc->len) >= 0x22) {
		if (gc->is_PCI)
			hd->bustype = IS_PCI;
		else if (gc->is_EISA)
			hd->bustype = IS_EISA;
		else
			hd->bustype = IS_ISA;
	} else {
		if (buff[21] == '4')
			hd->bustype = IS_PCI;
		else if (buff[21] == '2')
			hd->bustype = IS_EISA;
		else
			hd->bustype = IS_ISA;
	}

	SD(sh)->cplen = cplen;
	SD(sh)->cppadlen = cppadlen;
	SD(sh)->hostid = gc->scsi_id[3];
	SD(sh)->devflags = 1 << gc->scsi_id[3];
	SD(sh)->moresupport = gc->MORE_support;
	sh->unique_id = base;
	sh->base = base;
	sh->io_port = base;
	sh->n_io_port = 9;
	sh->irq = gc->IRQ;
	sh->dma_channel = PIO;
	sh->this_id = gc->scsi_id[3];
	sh->can_queue = 1;
	sh->cmd_per_lun = 1;
	sh->sg_tablesize = SG_ALL;

	hd->channel = 0;

	hd->pdev = pci_dev_get(pdev);	/* Keep a PCI reference */

	sh->max_id = 8;
	sh->max_lun = 8;

	if (gc->SECOND)
		hd->primary = 0;
	else
		hd->primary = 1;

	hd->next = NULL;	/* build a linked list of all HBAs */
	hd->prev = last_HBA;
	if (hd->prev != NULL)
		SD(hd->prev)->next = sh;
	last_HBA = sh;
	if (first_HBA == NULL)
		first_HBA = sh;
	registered_HBAs++;
	return (1);
}