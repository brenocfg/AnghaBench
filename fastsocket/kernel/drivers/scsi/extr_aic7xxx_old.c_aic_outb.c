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
struct aic7xxx_host {scalar_t__ base; scalar_t__ maddr; } ;

/* Variables and functions */
 scalar_t__ HCNTRL ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  outb (unsigned char,scalar_t__) ; 
 int /*<<< orphan*/  readb (scalar_t__) ; 
 int /*<<< orphan*/  writeb (unsigned char,scalar_t__) ; 

__attribute__((used)) static void
aic_outb(struct aic7xxx_host *p, unsigned char val, long port)
{
#ifdef MMAPIO
  if(p->maddr)
  {
    writeb(val, p->maddr + port);
    mb(); /* locked operation in order to force CPU ordering */
    readb(p->maddr + HCNTRL); /* dummy read to flush the PCI write */
  }
  else
  {
    outb(val, p->base + port);
    mb(); /* locked operation in order to force CPU ordering */
  }
#else
  outb(val, p->base + port);
  mb(); /* locked operation in order to force CPU ordering */
#endif
}