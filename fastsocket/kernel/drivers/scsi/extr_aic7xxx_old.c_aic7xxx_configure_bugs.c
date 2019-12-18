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
struct aic7xxx_host {int chip; int bugs; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
#define  AHC_AIC7850 136 
#define  AHC_AIC7860 135 
#define  AHC_AIC7870 134 
#define  AHC_AIC7880 133 
#define  AHC_AIC7890 132 
#define  AHC_AIC7892 131 
#define  AHC_AIC7895 130 
#define  AHC_AIC7896 129 
#define  AHC_AIC7899 128 
 int AHC_BUG_AUTOFLUSH ; 
 int AHC_BUG_CACHETHEN ; 
 int AHC_BUG_CACHETHEN_DIS ; 
 int AHC_BUG_PCI_2_1_RETRY ; 
 int AHC_BUG_PCI_MWI ; 
 int AHC_BUG_SCBCHAN_UPLOAD ; 
 int AHC_BUG_TMODE_WIDEODD ; 
 int AHC_CHIPID_MASK ; 
 int CACHETHEN ; 
 int /*<<< orphan*/  DSCOMMAND0 ; 
 int /*<<< orphan*/  PCI_COMMAND ; 
 unsigned short PCI_COMMAND_INVALIDATE ; 
 int aic_inb (struct aic7xxx_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aic_outb (struct aic7xxx_host*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned short*) ; 
 int /*<<< orphan*/  pci_write_config_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned short) ; 

__attribute__((used)) static void
aic7xxx_configure_bugs(struct aic7xxx_host *p)
{
  unsigned short tmp_word;
 
  switch(p->chip & AHC_CHIPID_MASK)
  {
    case AHC_AIC7860:
      p->bugs |= AHC_BUG_PCI_2_1_RETRY;
      /* fall through */
    case AHC_AIC7850:
    case AHC_AIC7870:
      p->bugs |= AHC_BUG_TMODE_WIDEODD | AHC_BUG_CACHETHEN | AHC_BUG_PCI_MWI;
      break;
    case AHC_AIC7880:
      p->bugs |= AHC_BUG_TMODE_WIDEODD | AHC_BUG_PCI_2_1_RETRY |
                 AHC_BUG_CACHETHEN | AHC_BUG_PCI_MWI;
      break;
    case AHC_AIC7890:
      p->bugs |= AHC_BUG_AUTOFLUSH | AHC_BUG_CACHETHEN;
      break;
    case AHC_AIC7892:
      p->bugs |= AHC_BUG_SCBCHAN_UPLOAD;
      break;
    case AHC_AIC7895:
      p->bugs |= AHC_BUG_TMODE_WIDEODD | AHC_BUG_PCI_2_1_RETRY |
                 AHC_BUG_CACHETHEN | AHC_BUG_PCI_MWI;
      break;
    case AHC_AIC7896:
      p->bugs |= AHC_BUG_CACHETHEN_DIS;
      break;
    case AHC_AIC7899:
      p->bugs |= AHC_BUG_SCBCHAN_UPLOAD;
      break;
    default:
      /* Nothing to do */
      break;
  }

  /*
   * Now handle the bugs that require PCI register or card register tweaks
   */
  pci_read_config_word(p->pdev, PCI_COMMAND, &tmp_word);
  if(p->bugs & AHC_BUG_PCI_MWI)
  {
    tmp_word &= ~PCI_COMMAND_INVALIDATE;
  }
  else
  {
    tmp_word |= PCI_COMMAND_INVALIDATE;
  }
  pci_write_config_word(p->pdev, PCI_COMMAND, tmp_word);

  if(p->bugs & AHC_BUG_CACHETHEN)
  {
    aic_outb(p, aic_inb(p, DSCOMMAND0) & ~CACHETHEN, DSCOMMAND0);
  }
  else if (p->bugs & AHC_BUG_CACHETHEN_DIS)
  {
    aic_outb(p, aic_inb(p, DSCOMMAND0) | CACHETHEN, DSCOMMAND0);
  }

  return;
}