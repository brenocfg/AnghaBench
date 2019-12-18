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
typedef  int /*<<< orphan*/  u64 ;
struct srp_internal {TYPE_1__* f; } ;
struct Scsi_Host {int /*<<< orphan*/  transportt; } ;
struct TYPE_2__ {int (* it_nexus_response ) (struct Scsi_Host*,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int stub1 (struct Scsi_Host*,int /*<<< orphan*/ ,int) ; 
 struct srp_internal* to_srp_internal (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int srp_it_nexus_response(struct Scsi_Host *shost, u64 nexus, int result)
{
	struct srp_internal *i = to_srp_internal(shost->transportt);
	return i->f->it_nexus_response(shost, nexus, result);
}