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
struct aic7xxx_host {int chip; size_t board_name_index; int features; int /*<<< orphan*/  pci_device_fn; int /*<<< orphan*/  pci_bus; } ;
struct TYPE_2__ {int member_0; int member_1; int member_2; int member_3; int member_4; int member_5; int member_6; int member_7; int member_8; int member_9; int member_10; int member_11; int member_12; int member_13; int member_14; int member_15; int member_16; int member_17; int member_18; int member_19; int member_20; int member_21; int member_22; int member_23; int member_24; int member_25; int member_26; int member_27; int member_28; int member_29; int member_30; int member_31; } ;

/* Variables and functions */
 int AHC_CHIPID_MASK ; 
#define  AHC_EISA 130 
#define  AHC_PCI 129 
 int AHC_QUEUE_REGS ; 
#define  AHC_VL 128 
 int /*<<< orphan*/  HNSCB_QOFF ; 
 int /*<<< orphan*/  PCI_FUNC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCI_SLOT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDSCB_QOFF ; 
 int /*<<< orphan*/  SNSCB_QOFF ; 
 int /*<<< orphan*/  aic_inb (struct aic7xxx_host*,int) ; 
 int /*<<< orphan*/  aic_outb (struct aic7xxx_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * board_names ; 
 int /*<<< orphan*/  printk (char*,...) ; 

__attribute__((used)) static void
aic7xxx_print_card(struct aic7xxx_host *p)
{
  int i, j, k, chip;
  static struct register_ranges {
    int num_ranges;
    int range_val[32];
  } cards_ds[] = {
    { 0, {0,} }, /* none */
    {10, {0x00, 0x05, 0x08, 0x11, 0x18, 0x19, 0x1f, 0x1f, 0x60, 0x60, /*7771*/
          0x62, 0x66, 0x80, 0x8e, 0x90, 0x95, 0x97, 0x97, 0x9b, 0x9f} },
    { 9, {0x00, 0x05, 0x08, 0x11, 0x18, 0x1f, 0x60, 0x60, 0x62, 0x66, /*7850*/
          0x80, 0x8e, 0x90, 0x95, 0x97, 0x97, 0x9a, 0x9f} },
    { 9, {0x00, 0x05, 0x08, 0x11, 0x18, 0x1f, 0x60, 0x60, 0x62, 0x66, /*7860*/
          0x80, 0x8e, 0x90, 0x95, 0x97, 0x97, 0x9a, 0x9f} },
    {10, {0x00, 0x05, 0x08, 0x11, 0x18, 0x19, 0x1c, 0x1f, 0x60, 0x60, /*7870*/
          0x62, 0x66, 0x80, 0x8e, 0x90, 0x95, 0x97, 0x97, 0x9a, 0x9f} },
    {10, {0x00, 0x05, 0x08, 0x11, 0x18, 0x1a, 0x1c, 0x1f, 0x60, 0x60, /*7880*/
          0x62, 0x66, 0x80, 0x8e, 0x90, 0x95, 0x97, 0x97, 0x9a, 0x9f} },
    {16, {0x00, 0x05, 0x08, 0x11, 0x18, 0x1f, 0x60, 0x60, 0x62, 0x66, /*7890*/
          0x84, 0x8e, 0x90, 0x95, 0x97, 0x97, 0x9a, 0x9a, 0x9f, 0x9f,
          0xe0, 0xf1, 0xf4, 0xf4, 0xf6, 0xf6, 0xf8, 0xf8, 0xfa, 0xfc,
          0xfe, 0xff} },
    {12, {0x00, 0x05, 0x08, 0x11, 0x18, 0x19, 0x1b, 0x1f, 0x60, 0x60, /*7895*/
          0x62, 0x66, 0x80, 0x8e, 0x90, 0x95, 0x97, 0x97, 0x9a, 0x9a,
          0x9f, 0x9f, 0xe0, 0xf1} },
    {16, {0x00, 0x05, 0x08, 0x11, 0x18, 0x1f, 0x60, 0x60, 0x62, 0x66, /*7896*/
          0x84, 0x8e, 0x90, 0x95, 0x97, 0x97, 0x9a, 0x9a, 0x9f, 0x9f,
          0xe0, 0xf1, 0xf4, 0xf4, 0xf6, 0xf6, 0xf8, 0xf8, 0xfa, 0xfc,
          0xfe, 0xff} },
    {12, {0x00, 0x05, 0x08, 0x11, 0x18, 0x1f, 0x60, 0x60, 0x62, 0x66, /*7892*/
          0x84, 0x8e, 0x90, 0x95, 0x97, 0x97, 0x9a, 0x9a, 0x9c, 0x9f,
          0xe0, 0xf1, 0xf4, 0xfc} },
    {12, {0x00, 0x05, 0x08, 0x11, 0x18, 0x1f, 0x60, 0x60, 0x62, 0x66, /*7899*/
          0x84, 0x8e, 0x90, 0x95, 0x97, 0x97, 0x9a, 0x9a, 0x9c, 0x9f,
          0xe0, 0xf1, 0xf4, 0xfc} },
  };
  chip = p->chip & AHC_CHIPID_MASK;
  printk("%s at ",
         board_names[p->board_name_index]);
  switch(p->chip & ~AHC_CHIPID_MASK)
  {
    case AHC_VL:
      printk("VLB Slot %d.\n", p->pci_device_fn);
      break;
    case AHC_EISA:
      printk("EISA Slot %d.\n", p->pci_device_fn);
      break;
    case AHC_PCI:
    default:
      printk("PCI %d/%d/%d.\n", p->pci_bus, PCI_SLOT(p->pci_device_fn),
             PCI_FUNC(p->pci_device_fn));
      break;
  }

  /*
   * the registers on the card....
   */
  printk("Card Dump:\n");
  k = 0;
  for(i=0; i<cards_ds[chip].num_ranges; i++)
  {
    for(j  = cards_ds[chip].range_val[ i * 2 ];
        j <= cards_ds[chip].range_val[ i * 2 + 1 ] ;
        j++)
    {
      printk("%02x:%02x ", j, aic_inb(p, j));
      if(++k == 13)
      {
        printk("\n");
        k=0;
      }
    }
  }
  if(k != 0)
    printk("\n");

  /*
   * If this was an Ultra2 controller, then we just hosed the card in terms
   * of the QUEUE REGS.  This function is only called at init time or by
   * the panic_abort function, so it's safe to assume a generic init time
   * setting here
   */

  if(p->features & AHC_QUEUE_REGS)
  {
    aic_outb(p, 0, SDSCB_QOFF);
    aic_outb(p, 0, SNSCB_QOFF);
    aic_outb(p, 0, HNSCB_QOFF);
  }

}