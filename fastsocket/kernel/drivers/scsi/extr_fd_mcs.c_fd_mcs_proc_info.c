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
struct Scsi_Host {int host_no; } ;
typedef  int off_t ;

/* Variables and functions */
 int Bytes_Read ; 
 int Bytes_Written ; 
 char* DRIVER_VERSION ; 
 int ENOSYS ; 
 int FIFO_COUNT ; 
 int FIFO_Size ; 
 int INTR_Processed ; 
 int TOTAL_INTR ; 
 char* adapter_name ; 
 scalar_t__ sprintf (char*,char*,...) ; 

__attribute__((used)) static int fd_mcs_proc_info(struct Scsi_Host *shpnt, char *buffer, char **start, off_t offset, int length, int inout)
{
	int len = 0;

	if (inout)
		return (-ENOSYS);

	*start = buffer + offset;

	len += sprintf(buffer + len, "Future Domain MCS-600/700 Driver %s\n", DRIVER_VERSION);
	len += sprintf(buffer + len, "HOST #%d: %s\n", shpnt->host_no, adapter_name);
	len += sprintf(buffer + len, "FIFO Size=0x%x, FIFO Count=%d\n", FIFO_Size, FIFO_COUNT);
	len += sprintf(buffer + len, "DriverCalls=%d, Interrupts=%d, BytesRead=%d, BytesWrite=%d\n\n", TOTAL_INTR, INTR_Processed, Bytes_Read, Bytes_Written);

	if ((len -= offset) <= 0)
		return 0;
	if (len > length)
		len = length;
	return len;
}