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
struct aic7xxx_host {int features; } ;

/* Variables and functions */
 int AHC_MORE_SRAM ; 
 int SEQCTL ; 
 int SRAM_BASE ; 
 int TARG_OFFSET ; 
 int /*<<< orphan*/  aic_inb (struct aic7xxx_host*,int) ; 
 int /*<<< orphan*/  printk (char*,...) ; 

__attribute__((used)) static void
aic7xxx_print_scratch_ram(struct aic7xxx_host *p)
{
  int i, k;

  k = 0;
  printk("Scratch RAM:\n");
  for(i = SRAM_BASE; i < SEQCTL; i++)
  {
    printk("%02x:%02x ", i, aic_inb(p, i));
    if(++k == 13)
    {
      printk("\n");
      k=0;
    }
  }
  if (p->features & AHC_MORE_SRAM)
  {
    for(i = TARG_OFFSET; i < 0x80; i++)
    {
      printk("%02x:%02x ", i, aic_inb(p, i));
      if(++k == 13)
      {
        printk("\n");
        k=0;
      }
    }
  }
  printk("\n");
}