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
 int pmon_makeb64 (int,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*) ; 

__attribute__((used)) static int
pmon_checkset (int recsize, char **buff, int *value)
{
  int count;

  /* Add the checksum (without updating the value): */
  sprintf (*buff, "/C");
  count = pmon_makeb64 (*value, (*buff + 2), 12, NULL);
  *buff += (count + 2);
  sprintf (*buff, "\n");
  *buff += 2;			/* include zero terminator */
  /* Forcing a checksum validation clears the sum: */
  *value = 0;
  return (recsize + count + 3);
}