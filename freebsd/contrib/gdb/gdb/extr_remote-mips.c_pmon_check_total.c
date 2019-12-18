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
 int /*<<< orphan*/  mips_expect (char*) ; 
 int mips_expect_download (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static int
pmon_check_total (int bintotal)
{
  char hexnumber[9];		/* includes '\0' space */
  mips_expect ("\r\ntotal = 0x");
  sprintf (hexnumber, "%x", bintotal);
  mips_expect (hexnumber);
  return mips_expect_download (" bytes\r\n");
}