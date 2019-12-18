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
typedef  int off_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int /*<<< orphan*/  CAP_SYS_RAWIO ; 
 int EACCES ; 
 int EINVAL ; 
 char* SCSI_DEBUG_VERSION ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int dif_errors ; 
 int dix_reads ; 
 int dix_writes ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int num_aborts ; 
 int num_bus_resets ; 
 int num_dev_resets ; 
 int num_host_resets ; 
 int scsi_debug_cmnd_count ; 
 int scsi_debug_delay ; 
 int scsi_debug_dev_size_mb ; 
 scalar_t__ scsi_debug_every_nth ; 
 int scsi_debug_max_luns ; 
 int scsi_debug_num_tgts ; 
 int scsi_debug_opts ; 
 int scsi_debug_scsi_level ; 
 int scsi_debug_sector_size ; 
 char* scsi_debug_version_date ; 
 int sdebug_cylinders_per ; 
 int sdebug_heads ; 
 int sdebug_sectors_per ; 
 int sprintf (char*,char*,char*,char*,int,int,int,scalar_t__,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int) ; 
 int sscanf (char*,char*,int*) ; 

__attribute__((used)) static int scsi_debug_proc_info(struct Scsi_Host *host, char *buffer, char **start, off_t offset,
				int length, int inout)
{
	int len, pos, begin;
	int orig_length;

	orig_length = length;

	if (inout == 1) {
		char arr[16];
		int minLen = length > 15 ? 15 : length;

		if (!capable(CAP_SYS_ADMIN) || !capable(CAP_SYS_RAWIO))
			return -EACCES;
		memcpy(arr, buffer, minLen);
		arr[minLen] = '\0';
		if (1 != sscanf(arr, "%d", &pos))
			return -EINVAL;
		scsi_debug_opts = pos;
		if (scsi_debug_every_nth != 0)
                        scsi_debug_cmnd_count = 0;
		return length;
	}
	begin = 0;
	pos = len = sprintf(buffer, "scsi_debug adapter driver, version "
	    "%s [%s]\n"
	    "num_tgts=%d, shared (ram) size=%d MB, opts=0x%x, "
	    "every_nth=%d(curr:%d)\n"
	    "delay=%d, max_luns=%d, scsi_level=%d\n"
	    "sector_size=%d bytes, cylinders=%d, heads=%d, sectors=%d\n"
	    "number of aborts=%d, device_reset=%d, bus_resets=%d, "
	    "host_resets=%d\ndix_reads=%d dix_writes=%d dif_errors=%d\n",
	    SCSI_DEBUG_VERSION, scsi_debug_version_date, scsi_debug_num_tgts,
	    scsi_debug_dev_size_mb, scsi_debug_opts, scsi_debug_every_nth,
	    scsi_debug_cmnd_count, scsi_debug_delay,
	    scsi_debug_max_luns, scsi_debug_scsi_level,
	    scsi_debug_sector_size, sdebug_cylinders_per, sdebug_heads,
	    sdebug_sectors_per, num_aborts, num_dev_resets, num_bus_resets,
	    num_host_resets, dix_reads, dix_writes, dif_errors);
	if (pos < offset) {
		len = 0;
		begin = pos;
	}
	*start = buffer + (offset - begin);	/* Start of wanted data */
	len -= (offset - begin);
	if (len > length)
		len = length;
	return len;
}