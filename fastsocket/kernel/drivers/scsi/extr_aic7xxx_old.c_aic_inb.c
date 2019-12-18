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
 unsigned char inb (scalar_t__) ; 
 unsigned char readb (scalar_t__) ; 

__attribute__((used)) static unsigned char
aic_inb(struct aic7xxx_host *p, long port)
{
#ifdef MMAPIO
  unsigned char x;
  if(p->maddr)
  {
    x = readb(p->maddr + port);
  }
  else
  {
    x = inb(p->base + port);
  }
  return(x);
#else
  return(inb(p->base + port));
#endif
}