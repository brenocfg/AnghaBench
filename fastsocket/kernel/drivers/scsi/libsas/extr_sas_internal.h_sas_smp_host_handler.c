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
struct request {int dummy; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  shost_printk (int /*<<< orphan*/ ,struct Scsi_Host*,char*) ; 

__attribute__((used)) static inline int sas_smp_host_handler(struct Scsi_Host *shost,
				       struct request *req,
				       struct request *rsp)
{
	shost_printk(KERN_ERR, shost,
		"Cannot send SMP to a sas host (not enabled in CONFIG)\n");
	return -EINVAL;
}