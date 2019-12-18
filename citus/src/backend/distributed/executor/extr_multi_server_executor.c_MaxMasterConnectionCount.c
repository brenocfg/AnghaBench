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
 int Max (int,int) ; 
 int RESERVED_FD_COUNT ; 
 int max_files_per_process ; 

int
MaxMasterConnectionCount(void)
{
	return Max((max_files_per_process - RESERVED_FD_COUNT) / 2, 1);
}