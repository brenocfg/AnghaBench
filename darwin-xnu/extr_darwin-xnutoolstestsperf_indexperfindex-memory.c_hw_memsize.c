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
typedef  int /*<<< orphan*/  my_memsize ;

/* Variables and functions */
 int CTL_HW ; 
 int HW_MEMSIZE ; 
 int sysctl (int*,int,size_t*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

size_t hw_memsize(void) {
  int mib[2];
  size_t len;
  size_t my_memsize;
  int retval;

  mib[0] = CTL_HW;
  mib[1] = HW_MEMSIZE;
  len = sizeof(my_memsize);

  retval = sysctl(mib, 2, &my_memsize, &len, NULL, 0);

  if(retval != 0)
      return 0;

  return my_memsize;
}