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
struct TYPE_2__ {size_t ipbfln1f; int ipflags1; int /*<<< orphan*/  iptrgcls; int /*<<< orphan*/  ippathid; int /*<<< orphan*/  ipmsgid; void* ipbfadr1; } ;
union iucv_param {TYPE_1__ db; } ;
typedef  int u8 ;
typedef  void* u32 ;
struct iucv_path {int /*<<< orphan*/  pathid; } ;
struct iucv_message {int flags; int /*<<< orphan*/  class; int /*<<< orphan*/  id; } ;
typedef  scalar_t__ addr_t ;

/* Variables and functions */
 int EIO ; 
 int IUCV_IPFGMID ; 
 int IUCV_IPFGPID ; 
 int IUCV_IPRMDATA ; 
 int IUCV_IPTRGCLS ; 
 int /*<<< orphan*/  IUCV_RECEIVE ; 
 scalar_t__ cpus_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iucv_buffer_cpumask ; 
 int iucv_call_b2f0 (int /*<<< orphan*/ ,union iucv_param*) ; 
 int iucv_message_receive_iprmdata (struct iucv_path*,struct iucv_message*,int,void*,size_t,size_t*) ; 
 union iucv_param** iucv_param ; 
 int /*<<< orphan*/  memset (union iucv_param*,int /*<<< orphan*/ ,int) ; 
 size_t smp_processor_id () ; 

int __iucv_message_receive(struct iucv_path *path, struct iucv_message *msg,
			   u8 flags, void *buffer, size_t size, size_t *residual)
{
	union iucv_param *parm;
	int rc;

	if (msg->flags & IUCV_IPRMDATA)
		return iucv_message_receive_iprmdata(path, msg, flags,
						     buffer, size, residual);
	if (cpus_empty(iucv_buffer_cpumask)) {
		rc = -EIO;
		goto out;
	}
	parm = iucv_param[smp_processor_id()];
	memset(parm, 0, sizeof(union iucv_param));
	parm->db.ipbfadr1 = (u32)(addr_t) buffer;
	parm->db.ipbfln1f = (u32) size;
	parm->db.ipmsgid = msg->id;
	parm->db.ippathid = path->pathid;
	parm->db.iptrgcls = msg->class;
	parm->db.ipflags1 = (flags | IUCV_IPFGPID |
			     IUCV_IPFGMID | IUCV_IPTRGCLS);
	rc = iucv_call_b2f0(IUCV_RECEIVE, parm);
	if (!rc || rc == 5) {
		msg->flags = parm->db.ipflags1;
		if (residual)
			*residual = parm->db.ipbfln1f;
	}
out:
	return rc;
}