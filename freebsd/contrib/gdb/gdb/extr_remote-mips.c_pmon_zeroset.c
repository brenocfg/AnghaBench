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

/* Variables and functions */
 int pmon_makeb64 (int,char*,int,unsigned int*) ; 
 int /*<<< orphan*/  sprintf (char*,char*) ; 

__attribute__((used)) static int
pmon_zeroset (int recsize, char **buff, int *amount, unsigned int *chksum)
{
  int count;

  sprintf (*buff, "/Z");
  count = pmon_makeb64 (*amount, (*buff + 2), 12, chksum);
  *buff += (count + 2);
  *amount = 0;
  return (recsize + count + 2);
}