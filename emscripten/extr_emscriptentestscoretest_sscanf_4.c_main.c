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
 int /*<<< orphan*/  printf (char*,...) ; 
 int sscanf (char*,char*,char*,char*,char*) ; 

int main() {
  char pYear[16], pMonth[16], pDay[16], pDate[64];
  printf("%d\n", sscanf("Nov 19 2012", "%s%s%s", pMonth, pDay, pYear));
  printf("day %s, month %s, year %s \n", pDay, pMonth, pYear);
  return (0);
}