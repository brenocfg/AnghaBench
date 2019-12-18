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
struct Scsi_Host {int dummy; } ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int sprintf (char*,char*) ; 

__attribute__((used)) static int tcm_loop_proc_info(struct Scsi_Host *host, char *buffer,
				char **start, off_t offset,
				int length, int inout)
{
	return sprintf(buffer, "tcm_loop_proc_info()\n");
}