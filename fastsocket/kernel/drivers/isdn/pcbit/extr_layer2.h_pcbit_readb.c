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
struct pcbit_dev {scalar_t__ readptr; scalar_t__ sh_mem; } ;

/* Variables and functions */
 scalar_t__ BANK2 ; 
 scalar_t__ BANKLEN ; 
 unsigned char readb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline__ unsigned char pcbit_readb(struct pcbit_dev *dev)
{
  unsigned char val;

  val = readb(dev->readptr++);
  if (dev->readptr == dev->sh_mem + BANK2 + BANKLEN)
    dev->readptr = dev->sh_mem + BANK2;

  return val;
}