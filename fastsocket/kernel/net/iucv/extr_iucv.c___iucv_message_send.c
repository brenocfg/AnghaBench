#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int ipflags1; int /*<<< orphan*/  ipmsgid; int /*<<< orphan*/  ipmsgtag; void* ipsrccls; int /*<<< orphan*/  iptrgcls; int /*<<< orphan*/  ippathid; void* ipbfln1f; void* ipbfadr1; } ;
struct TYPE_3__ {int ipflags1; int /*<<< orphan*/  iprmmsg; int /*<<< orphan*/  ipmsgtag; void* ipsrccls; int /*<<< orphan*/  iptrgcls; int /*<<< orphan*/  ippathid; } ;
union iucv_param {TYPE_2__ db; TYPE_1__ dpl; } ;
typedef  int u8 ;
typedef  void* u32 ;
struct iucv_path {int /*<<< orphan*/  pathid; } ;
struct iucv_message {int /*<<< orphan*/  id; int /*<<< orphan*/  tag; int /*<<< orphan*/  class; } ;
typedef  scalar_t__ addr_t ;

/* Variables and functions */
 int EIO ; 
 int IUCV_IPNORPY ; 
 int IUCV_IPRMDATA ; 
 int /*<<< orphan*/  IUCV_SEND ; 
 scalar_t__ cpus_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iucv_buffer_cpumask ; 
 int iucv_call_b2f0 (int /*<<< orphan*/ ,union iucv_param*) ; 
 union iucv_param** iucv_param ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  memset (union iucv_param*,int /*<<< orphan*/ ,int) ; 
 size_t smp_processor_id () ; 

int __iucv_message_send(struct iucv_path *path, struct iucv_message *msg,
		      u8 flags, u32 srccls, void *buffer, size_t size)
{
	union iucv_param *parm;
	int rc;

	if (cpus_empty(iucv_buffer_cpumask)) {
		rc = -EIO;
		goto out;
	}
	parm = iucv_param[smp_processor_id()];
	memset(parm, 0, sizeof(union iucv_param));
	if (flags & IUCV_IPRMDATA) {
		/* Message of 8 bytes can be placed into the parameter list. */
		parm->dpl.ippathid = path->pathid;
		parm->dpl.ipflags1 = flags | IUCV_IPNORPY;
		parm->dpl.iptrgcls = msg->class;
		parm->dpl.ipsrccls = srccls;
		parm->dpl.ipmsgtag = msg->tag;
		memcpy(parm->dpl.iprmmsg, buffer, 8);
	} else {
		parm->db.ipbfadr1 = (u32)(addr_t) buffer;
		parm->db.ipbfln1f = (u32) size;
		parm->db.ippathid = path->pathid;
		parm->db.ipflags1 = flags | IUCV_IPNORPY;
		parm->db.iptrgcls = msg->class;
		parm->db.ipsrccls = srccls;
		parm->db.ipmsgtag = msg->tag;
	}
	rc = iucv_call_b2f0(IUCV_SEND, parm);
	if (!rc)
		msg->id = parm->db.ipmsgid;
out:
	return rc;
}