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

/* Variables and functions */
 char* SCSI_DEBUG_VERSION ; 
 int scsi_debug_dev_size_mb ; 
 int scsi_debug_opts ; 
 char* scsi_debug_version_date ; 
 char const* sdebug_info ; 
 int /*<<< orphan*/  sprintf (char const*,char*,char*,char*,int,int) ; 

__attribute__((used)) static const char * scsi_debug_info(struct Scsi_Host * shp)
{
	sprintf(sdebug_info, "scsi_debug, version %s [%s], "
		"dev_size_mb=%d, opts=0x%x", SCSI_DEBUG_VERSION,
		scsi_debug_version_date, scsi_debug_dev_size_mb,
		scsi_debug_opts);
	return sdebug_info;
}