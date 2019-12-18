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
typedef  int u_int8_t ;
struct TYPE_9__ {int type; } ;
struct pf_rule_addr {TYPE_1__ addr; } ;
struct TYPE_11__ {int /*<<< orphan*/  addr32; } ;
struct TYPE_10__ {int /*<<< orphan*/  addr32; } ;
struct TYPE_12__ {TYPE_3__ mask; TYPE_2__ addr; } ;
struct TYPE_13__ {int /*<<< orphan*/  rtlabelname; TYPE_4__ a; int /*<<< orphan*/  tblname; int /*<<< orphan*/  ifname; } ;
struct TYPE_16__ {TYPE_5__ v; int /*<<< orphan*/  iflags; int /*<<< orphan*/  type; } ;
struct TYPE_14__ {int /*<<< orphan*/  op; int /*<<< orphan*/ * port; } ;
struct TYPE_15__ {TYPE_6__ range; } ;
typedef  int /*<<< orphan*/  MD5_CTX ;

/* Variables and functions */
#define  IPPROTO_TCP 133 
#define  IPPROTO_UDP 132 
#define  PF_ADDR_ADDRMASK 131 
#define  PF_ADDR_DYNIFTL 130 
#define  PF_ADDR_RTLABEL 129 
#define  PF_ADDR_TABLE 128 
 int /*<<< orphan*/  PF_MD5_UPD (struct pf_rule_addr*,int /*<<< orphan*/ ) ; 
 TYPE_8__ addr ; 
 int /*<<< orphan*/  neg ; 
 TYPE_7__ xport ; 

__attribute__((used)) static void
pf_hash_rule_addr(MD5_CTX *ctx, struct pf_rule_addr *pfr, u_int8_t proto)
{
	PF_MD5_UPD(pfr, addr.type);
	switch (pfr->addr.type) {
	case PF_ADDR_DYNIFTL:
		PF_MD5_UPD(pfr, addr.v.ifname);
		PF_MD5_UPD(pfr, addr.iflags);
		break;
	case PF_ADDR_TABLE:
		PF_MD5_UPD(pfr, addr.v.tblname);
		break;
	case PF_ADDR_ADDRMASK:
		/* XXX ignore af? */
		PF_MD5_UPD(pfr, addr.v.a.addr.addr32);
		PF_MD5_UPD(pfr, addr.v.a.mask.addr32);
		break;
	case PF_ADDR_RTLABEL:
		PF_MD5_UPD(pfr, addr.v.rtlabelname);
		break;
	}

	switch (proto) {
	case IPPROTO_TCP:
	case IPPROTO_UDP:
		PF_MD5_UPD(pfr, xport.range.port[0]);
		PF_MD5_UPD(pfr, xport.range.port[1]);
		PF_MD5_UPD(pfr, xport.range.op);
		break;

	default:
		break;
	}

	PF_MD5_UPD(pfr, neg);
}