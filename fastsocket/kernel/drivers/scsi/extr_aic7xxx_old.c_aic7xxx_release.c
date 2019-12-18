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
struct aic7xxx_host {struct aic7xxx_host* next; int /*<<< orphan*/  pdev; int /*<<< orphan*/  base; scalar_t__ maddr; scalar_t__ irq; } ;
struct Scsi_Host {scalar_t__ hostdata; } ;

/* Variables and functions */
 scalar_t__ MAXREG ; 
 scalar_t__ MINREG ; 
 int /*<<< orphan*/  aic7xxx_free (struct aic7xxx_host*) ; 
 struct aic7xxx_host* first_aic7xxx ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct aic7xxx_host*) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  pci_dev_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
aic7xxx_release(struct Scsi_Host *host)
{
  struct aic7xxx_host *p = (struct aic7xxx_host *) host->hostdata;
  struct aic7xxx_host *next, *prev;

  if(p->irq)
    free_irq(p->irq, p);
#ifdef MMAPIO
  if(p->maddr)
  {
    iounmap(p->maddr);
  }
#endif /* MMAPIO */
  if(!p->pdev)
    release_region(p->base, MAXREG - MINREG);
#ifdef CONFIG_PCI
  else {
    pci_release_regions(p->pdev);
    pci_dev_put(p->pdev);
  }
#endif
  prev = NULL;
  next = first_aic7xxx;
  while(next != NULL)
  {
    if(next == p)
    {
      if(prev == NULL)
        first_aic7xxx = next->next;
      else
        prev->next = next->next;
    }
    else
    {
      prev = next;
    }
    next = next->next;
  }
  aic7xxx_free(p);
  return(0);
}