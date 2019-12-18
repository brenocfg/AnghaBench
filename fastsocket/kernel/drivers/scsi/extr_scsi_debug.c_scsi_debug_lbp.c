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
 unsigned int scsi_debug_lbpu ; 
 unsigned int scsi_debug_lbpws ; 
 unsigned int scsi_debug_lbpws10 ; 

__attribute__((used)) static unsigned int scsi_debug_lbp(void)
{
	return scsi_debug_lbpu | scsi_debug_lbpws | scsi_debug_lbpws10;
}