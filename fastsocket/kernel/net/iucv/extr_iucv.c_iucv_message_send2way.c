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
struct TYPE_4__ {int /*<<< orphan*/  ipmsgid; void* ipbfln2f; void* ipbfadr2; void* ipbfln1f; void* ipbfadr1; int /*<<< orphan*/  ipmsgtag; void* ipsrccls; int /*<<< orphan*/  iptrgcls; int /*<<< orphan*/  ipflags1; int /*<<< orphan*/  ippathid; } ;
struct TYPE_3__ {int /*<<< orphan*/  iprmmsg; void* ipbfln2f; void* ipbfadr2; int /*<<< orphan*/  ipmsgtag; void* ipsrccls; int /*<<< orphan*/  iptrgcls; int /*<<< orphan*/  ipflags1; int /*<<< orphan*/  ippathid; } ;
union iucv_param {TYPE_2__ db; TYPE_1__ dpl; } ;
typedef  int u8 ;
typedef  void* u32 ;
struct iucv_path {int /*<<< orphan*/  flags; int /*<<< orphan*/  pathid; } ;
struct iucv_message {int /*<<< orphan*/  id; int /*<<< orphan*/  tag; int /*<<< orphan*/  class; } ;
typedef  scalar_t__ addr_t ;

/* Variables and functions */
 int EIO ; 
 int IUCV_IPRMDATA ; 
 int /*<<< orphan*/  IUCV_SEND ; 
 scalar_t__ cpus_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iucv_buffer_cpumask ; 
 int iucv_call_b2f0 (int /*<<< orphan*/ ,union iucv_param*) ; 
 union iucv_param** iucv_param ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  memset (union iucv_param*,int /*<<< orphan*/ ,int) ; 
 size_t smp_processor_id () ; 

int iucv_message_send2way(struct iucv_path *path, struct iucv_message *msg,
			  u8 flags, u32 srccls, void *buffer, size_t size,
			  void *answer, size_t asize, size_t *residual)
{
	union iucv_param *parm;
	int rc;

	local_bh_disable();
	if (cpus_empty(iucv_buffer_cpumask)) {
		rc = -EIO;
		goto out;
	}
	parm = iucv_param[smp_processor_id()];
	memset(parm, 0, sizeof(union iucv_param));
	if (flags & IUCV_IPRMDATA) {
		parm->dpl.ippathid = path->pathid;
		parm->dpl.ipflags1 = path->flags;	/* priority message */
		parm->dpl.iptrgcls = msg->class;
		parm->dpl.ipsrccls = srccls;
		parm->dpl.ipmsgtag = msg->tag;
		parm->dpl.ipbfadr2 = (u32)(addr_t) answer;
		parm->dpl.ipbfln2f = (u32) asize;
		memcpy(parm->dpl.iprmmsg, buffer, 8);
	} else {
		parm->db.ippathid = path->pathid;
		parm->db.ipflags1 = path->flags;	/* priority message */
		parm->db.iptrgcls = msg->class;
		parm->db.ipsrccls = srccls;
		parm->db.ipmsgtag = msg->tag;
		parm->db.ipbfadr1 = (u32)(addr_t) buffer;
		parm->db.ipbfln1f = (u32) size;
		parm->db.ipbfadr2 = (u32)(addr_t) answer;
		parm->db.ipbfln2f = (u32) asize;
	}
	rc = iucv_call_b2f0(IUCV_SEND, parm);
	if (!rc)
		msg->id = parm->db.ipmsgid;
out:
	local_bh_enable();
	return rc;
}