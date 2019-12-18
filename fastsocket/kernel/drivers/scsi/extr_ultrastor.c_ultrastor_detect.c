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
struct scsi_host_template {char* proc_name; } ;

/* Variables and functions */
 scalar_t__ ultrastor_14f_detect (struct scsi_host_template*) ; 
 scalar_t__ ultrastor_24f_detect (struct scsi_host_template*) ; 

__attribute__((used)) static int ultrastor_detect(struct scsi_host_template * tpnt)
{
	tpnt->proc_name = "ultrastor";
	return ultrastor_14f_detect(tpnt) || ultrastor_24f_detect(tpnt);
}