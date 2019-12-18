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
 int /*<<< orphan*/  memcpy_toio (int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static __inline__ void memcpy_topcbit(struct pcbit_dev * dev, u_char * data, 
				      int len)
{
  int diff;

  diff = len - (BANKLEN - (dev->writeptr - dev->sh_mem) );

  if (diff > 0)
    {
      memcpy_toio(dev->writeptr, data, len - diff);
      memcpy_toio(dev->sh_mem, data + (len - diff), diff);
      dev->writeptr = dev->sh_mem + diff;
    }
  else
    {
      memcpy_toio(dev->writeptr, data, len);

      dev->writeptr += len;
      if (diff == 0)
	dev->writeptr = dev->sh_mem;
    }
}