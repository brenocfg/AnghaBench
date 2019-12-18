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
struct pcbit_dev {int readptr; int sh_mem; } ;

/* Variables and functions */
 int BANK2 ; 
 int BANKLEN ; 
 int /*<<< orphan*/  memcpy_fromio (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static __inline__ void memcpy_frompcbit(struct pcbit_dev * dev, u_char * data, int len)
{
  int diff;

  diff = len - (BANKLEN - (dev->readptr - (dev->sh_mem + BANK2) ) ); 
  if (diff > 0)
    {
      memcpy_fromio(data, dev->readptr, len - diff);
      memcpy_fromio(data + (len - diff), dev->sh_mem + BANK2 , diff);
      dev->readptr = dev->sh_mem + BANK2 + diff;
    }
  else
    {
      memcpy_fromio(data, dev->readptr, len);
      dev->readptr += len;
      if (diff == 0)
	dev->readptr = dev->sh_mem + BANK2;
    }
}