#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct scsi_cmnd {TYPE_1__* device; } ;
struct TYPE_6__ {int msgout_len; unsigned char* msgoutbuf; } ;
typedef  TYPE_3__ nsp32_hw_data ;
struct TYPE_5__ {scalar_t__ hostdata; } ;
struct TYPE_4__ {TYPE_2__* host; } ;

/* Variables and functions */
 unsigned char EXTENDED_MESSAGE ; 
 unsigned char EXTENDED_SDTR ; 
 unsigned char EXTENDED_SDTR_LEN ; 

__attribute__((used)) static void nsp32_build_sdtr(struct scsi_cmnd    *SCpnt,
			     unsigned char period,
			     unsigned char offset)
{
	nsp32_hw_data *data = (nsp32_hw_data *)SCpnt->device->host->hostdata;
	int pos             = data->msgout_len;

	data->msgoutbuf[pos] = EXTENDED_MESSAGE;  pos++;
	data->msgoutbuf[pos] = EXTENDED_SDTR_LEN; pos++;
	data->msgoutbuf[pos] = EXTENDED_SDTR;     pos++;
	data->msgoutbuf[pos] = period;            pos++;
	data->msgoutbuf[pos] = offset;            pos++;

	data->msgout_len = pos;
}