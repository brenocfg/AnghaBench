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
typedef  int /*<<< orphan*/  u_char ;
struct pcbit_dev {int writeptr; int sh_mem; } ;

/* Variables and functions */
 int BANKLEN ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  writew (unsigned short,int) ; 

__attribute__((used)) static __inline__ void pcbit_writew(struct pcbit_dev *dev, unsigned short dt)
{
  int dist;

  dist = BANKLEN - (dev->writeptr - dev->sh_mem);
  switch (dist) {
  case 2:
    writew(dt, dev->writeptr);
    dev->writeptr = dev->sh_mem;
    break;
  case 1:
    writeb((u_char) (dt & 0x00ffU), dev->writeptr);    
    dev->writeptr = dev->sh_mem;
    writeb((u_char) (dt >> 8), dev->writeptr++);    
    break;
  default:
    writew(dt, dev->writeptr);
    dev->writeptr += 2;
    break;
  };
}