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
 int baudrate ; 
 char* dev_name ; 
 int /*<<< orphan*/  printf (char*,char*,int) ; 

__attribute__((used)) static void
st2000_files_info (void)
{
  printf ("\tAttached to %s at %d baud.\n",
	  dev_name, baudrate);
}