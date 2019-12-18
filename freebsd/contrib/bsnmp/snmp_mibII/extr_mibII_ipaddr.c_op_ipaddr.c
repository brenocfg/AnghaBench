#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
typedef  int u_char ;
struct TYPE_14__ {void* s_addr; } ;
struct TYPE_13__ {void* s_addr; } ;
struct update {int set; int ifindex; int bcast; TYPE_4__ mask; TYPE_3__ addr; } ;
struct TYPE_15__ {int integer; int* ipaddress; } ;
struct TYPE_16__ {int* subs; } ;
struct snmp_value {TYPE_5__ v; TYPE_6__ var; } ;
struct snmp_context {int dummy; } ;
struct TYPE_12__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_11__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_17__ {int* subs; } ;
struct mibifa {int ifindex; int flags; TYPE_2__ inbcast; TYPE_1__ inmask; TYPE_8__ index; } ;
struct asn_oid {int len; int* subs; } ;
typedef  enum snmp_op { ____Placeholder_snmp_op } snmp_op ;
typedef  int asn_subid_t ;

/* Variables and functions */
 struct mibifa* FIND_OBJECT_OID (int /*<<< orphan*/ *,TYPE_6__*,int) ; 
#define  LEAF_ipAdEntAddr 137 
#define  LEAF_ipAdEntBcastAddr 136 
#define  LEAF_ipAdEntIfIndex 135 
#define  LEAF_ipAdEntNetMask 134 
#define  LEAF_ipAdEntReasmMaxSize 133 
 int MIBIFA_DESTROYED ; 
 struct mibifa* NEXT_OBJECT_OID (int /*<<< orphan*/ *,TYPE_6__*,int) ; 
 int SNMP_ERR_INCONS_VALUE ; 
 int SNMP_ERR_NOERROR ; 
 int SNMP_ERR_NOSUCHNAME ; 
 int SNMP_ERR_NO_CREATION ; 
 int SNMP_ERR_RES_UNAVAIL ; 
 int SNMP_ERR_WRONG_VALUE ; 
#define  SNMP_OP_COMMIT 132 
#define  SNMP_OP_GET 131 
#define  SNMP_OP_GETNEXT 130 
#define  SNMP_OP_ROLLBACK 129 
#define  SNMP_OP_SET 128 
 int UPD_BCAST ; 
 int UPD_IFINDEX ; 
 int UPD_MASK ; 
 void* htonl (int) ; 
 int /*<<< orphan*/  index_append (TYPE_6__*,int,TYPE_8__*) ; 
 int /*<<< orphan*/  index_decode (TYPE_6__*,int,int,int*) ; 
 int /*<<< orphan*/  mibifa_list ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oid_ipAddrTable ; 
 scalar_t__ snmp_dep_lookup (struct snmp_context*,int /*<<< orphan*/ *,struct asn_oid*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_func ; 

int
op_ipaddr(struct snmp_context *ctx, struct snmp_value *value,
    u_int sub, u_int iidx, enum snmp_op op)
{
	asn_subid_t which;
	struct mibifa *ifa;
	struct update *upd;
	struct asn_oid idx;
	u_char ipaddr[4];

	which = value->var.subs[sub - 1];

	ifa = NULL;

	switch (op) {

	  case SNMP_OP_GETNEXT:
		if ((ifa = NEXT_OBJECT_OID(&mibifa_list, &value->var, sub)) == NULL)
			return (SNMP_ERR_NOSUCHNAME);
		index_append(&value->var, sub, &ifa->index);
		break;

	  case SNMP_OP_GET:
		if ((ifa = FIND_OBJECT_OID(&mibifa_list, &value->var, sub)) == NULL)
			return (SNMP_ERR_NOSUCHNAME);
		break;

	  case SNMP_OP_SET:
		if (index_decode(&value->var, sub, iidx, ipaddr))
			return (SNMP_ERR_NO_CREATION);
		ifa = FIND_OBJECT_OID(&mibifa_list, &value->var, sub);
		idx.len = 4;
		idx.subs[0] = ipaddr[0];
		idx.subs[1] = ipaddr[1];
		idx.subs[2] = ipaddr[2];
		idx.subs[3] = ipaddr[3];

		if ((upd = (struct update *)snmp_dep_lookup(ctx,
		    &oid_ipAddrTable, &idx, sizeof(*upd), update_func)) == NULL)
			return (SNMP_ERR_RES_UNAVAIL);

		upd->addr.s_addr = htonl((ipaddr[0] << 24) | (ipaddr[1] << 16) |
		    (ipaddr[2] << 8) | (ipaddr[3] << 0));

		switch (which) {

		  case LEAF_ipAdEntIfIndex:
			if (upd->set & UPD_IFINDEX)
				return (SNMP_ERR_INCONS_VALUE);
			if (value->v.integer < 0 ||
			    value->v.integer > 0x07fffffff)
				return (SNMP_ERR_WRONG_VALUE);
			if (ifa != NULL) {
				if (ifa->ifindex != (u_int)value->v.integer &&
				    value->v.integer != 0)
					return (SNMP_ERR_INCONS_VALUE);
			}
			upd->set |= UPD_IFINDEX;
			upd->ifindex = (u_int)value->v.integer;
			break;

		  case LEAF_ipAdEntNetMask:
			if (upd->set & UPD_MASK)
				return (SNMP_ERR_INCONS_VALUE);
			upd->mask.s_addr = htonl((value->v.ipaddress[0] << 24)
			    | (value->v.ipaddress[1] << 16)
			    | (value->v.ipaddress[2] << 8)
			    | (value->v.ipaddress[3] << 0));
			upd->set |= UPD_MASK;
			break;

		  case LEAF_ipAdEntBcastAddr:
			if (upd->set & UPD_BCAST)
				return (SNMP_ERR_INCONS_VALUE);
			if (value->v.integer != 0 && value->v.integer != 1)
				return (SNMP_ERR_WRONG_VALUE);
			upd->bcast = value->v.integer;
			upd->set |= UPD_BCAST;
			break;

		}
		return (SNMP_ERR_NOERROR);

	  case SNMP_OP_ROLLBACK:
	  case SNMP_OP_COMMIT:
		return (SNMP_ERR_NOERROR);
	}

	switch (which) {

	  case LEAF_ipAdEntAddr:
		value->v.ipaddress[0] = ifa->index.subs[0];
		value->v.ipaddress[1] = ifa->index.subs[1];
		value->v.ipaddress[2] = ifa->index.subs[2];
		value->v.ipaddress[3] = ifa->index.subs[3];
		break;

	  case LEAF_ipAdEntIfIndex:
		if (ifa->flags & MIBIFA_DESTROYED)
			value->v.integer = 0;
		else
			value->v.integer = ifa->ifindex;
		break;

	  case LEAF_ipAdEntNetMask:
		value->v.ipaddress[0] = (ntohl(ifa->inmask.s_addr) >> 24) & 0xff;
		value->v.ipaddress[1] = (ntohl(ifa->inmask.s_addr) >> 16) & 0xff;
		value->v.ipaddress[2] = (ntohl(ifa->inmask.s_addr) >>  8) & 0xff;
		value->v.ipaddress[3] = (ntohl(ifa->inmask.s_addr) >>  0) & 0xff;
		break;

	  case LEAF_ipAdEntBcastAddr:
		value->v.integer = ntohl(ifa->inbcast.s_addr) & 1;
		break;


	  case LEAF_ipAdEntReasmMaxSize:
		value->v.integer = 65535;
		break;
	}
	return (SNMP_ERR_NOERROR);
}