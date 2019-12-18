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
typedef  int u16 ;
struct MPT3SAS_ADAPTER {scalar_t__ sense_dma; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int SCSI_SENSE_BUFFERSIZE ; 
 int /*<<< orphan*/  cpu_to_le32 (scalar_t__) ; 

__le32
mpt3sas_base_get_sense_buffer_dma(struct MPT3SAS_ADAPTER *ioc, u16 smid)
{
	return cpu_to_le32(ioc->sense_dma + ((smid - 1) *
	    SCSI_SENSE_BUFFERSIZE));
}