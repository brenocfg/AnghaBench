#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint64_t ;
struct TYPE_15__ {int /*<<< orphan*/  inp6_hops; scalar_t__ inp6_ifindex; int /*<<< orphan*/  inp6_cksum; scalar_t__ inp6_hlim; } ;
struct TYPE_13__ {int /*<<< orphan*/  inp4_ip_tos; } ;
struct TYPE_11__ {int /*<<< orphan*/  inp6_local; } ;
struct TYPE_9__ {int /*<<< orphan*/  inp6_foreign; } ;
struct xinpcb_n {int xi_len; int /*<<< orphan*/  inp_flags2; int /*<<< orphan*/  inp_flowhash; TYPE_7__ inp_depend6; TYPE_5__ inp_depend4; TYPE_3__ inp_dependladdr; TYPE_1__ inp_dependfaddr; int /*<<< orphan*/  inp_ip_p; int /*<<< orphan*/  inp_ip_ttl; int /*<<< orphan*/  inp_vflag; int /*<<< orphan*/  inp_flow; int /*<<< orphan*/  inp_flags; int /*<<< orphan*/  inp_gencnt; void* inp_ppcb; int /*<<< orphan*/  inp_lport; int /*<<< orphan*/  inp_fport; void* xi_inpp; int /*<<< orphan*/  xi_kind; } ;
struct TYPE_16__ {int /*<<< orphan*/  inp6_hops; int /*<<< orphan*/  inp6_cksum; } ;
struct TYPE_14__ {int /*<<< orphan*/  inp4_ip_tos; } ;
struct TYPE_12__ {int /*<<< orphan*/  inp6_local; } ;
struct TYPE_10__ {int /*<<< orphan*/  inp6_foreign; } ;
struct inpcb {int /*<<< orphan*/  inp_flags2; int /*<<< orphan*/  inp_flowhash; TYPE_8__ inp_depend6; TYPE_6__ inp_depend4; TYPE_4__ inp_dependladdr; TYPE_2__ inp_dependfaddr; int /*<<< orphan*/  inp_ip_p; int /*<<< orphan*/  inp_ip_ttl; int /*<<< orphan*/  inp_vflag; int /*<<< orphan*/  inp_flow; int /*<<< orphan*/  inp_flags; int /*<<< orphan*/  inp_gencnt; struct inpcb* inp_ppcb; int /*<<< orphan*/  inp_lport; int /*<<< orphan*/  inp_fport; } ;

/* Variables and functions */
 scalar_t__ VM_KERNEL_ADDRPERM (struct inpcb*) ; 
 int /*<<< orphan*/  XSO_INPCB ; 

__attribute__((used)) static void
inpcb_to_xinpcb_n(struct inpcb *inp, struct xinpcb_n *xinp)
{
	xinp->xi_len = sizeof (struct xinpcb_n);
	xinp->xi_kind = XSO_INPCB;
	xinp->xi_inpp = (uint64_t)VM_KERNEL_ADDRPERM(inp);
	xinp->inp_fport = inp->inp_fport;
	xinp->inp_lport = inp->inp_lport;
	xinp->inp_ppcb = (uint64_t)VM_KERNEL_ADDRPERM(inp->inp_ppcb);
	xinp->inp_gencnt = inp->inp_gencnt;
	xinp->inp_flags = inp->inp_flags;
	xinp->inp_flow = inp->inp_flow;
	xinp->inp_vflag = inp->inp_vflag;
	xinp->inp_ip_ttl = inp->inp_ip_ttl;
	xinp->inp_ip_p = inp->inp_ip_p;
	xinp->inp_dependfaddr.inp6_foreign = inp->inp_dependfaddr.inp6_foreign;
	xinp->inp_dependladdr.inp6_local = inp->inp_dependladdr.inp6_local;
	xinp->inp_depend4.inp4_ip_tos = inp->inp_depend4.inp4_ip_tos;
	xinp->inp_depend6.inp6_hlim = 0;
	xinp->inp_depend6.inp6_cksum = inp->inp_depend6.inp6_cksum;
	xinp->inp_depend6.inp6_ifindex = 0;
	xinp->inp_depend6.inp6_hops = inp->inp_depend6.inp6_hops;
	xinp->inp_flowhash = inp->inp_flowhash;
	xinp->inp_flags2 = inp->inp_flags2;
}