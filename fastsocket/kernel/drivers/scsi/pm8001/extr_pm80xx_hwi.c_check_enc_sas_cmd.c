#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__* cdb; } ;
struct sas_task {TYPE_1__ ssp_task; } ;

/* Variables and functions */
 scalar_t__ READ_10 ; 
 scalar_t__ WRITE_10 ; 
 scalar_t__ WRITE_VERIFY ; 

__attribute__((used)) static int check_enc_sas_cmd(struct sas_task *task)
{
	if ((task->ssp_task.cdb[0] == READ_10)
		|| (task->ssp_task.cdb[0] == WRITE_10)
		|| (task->ssp_task.cdb[0] == WRITE_VERIFY))
		return 1;
	else
		return 0;
}