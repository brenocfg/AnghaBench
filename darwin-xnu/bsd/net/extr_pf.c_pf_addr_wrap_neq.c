#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  mask; int /*<<< orphan*/  addr; } ;
struct TYPE_8__ {int /*<<< orphan*/  rtlabel; TYPE_1__ a; } ;
struct TYPE_7__ {int /*<<< orphan*/  tbl; TYPE_2__* dyn; } ;
struct pf_addr_wrap {int type; TYPE_4__ v; TYPE_3__ p; } ;
struct TYPE_6__ {int /*<<< orphan*/  pfid_kt; } ;

/* Variables and functions */
#define  PF_ADDR_ADDRMASK 134 
#define  PF_ADDR_DYNIFTL 133 
#define  PF_ADDR_NOROUTE 132 
#define  PF_ADDR_RANGE 131 
#define  PF_ADDR_RTLABEL 130 
#define  PF_ADDR_TABLE 129 
#define  PF_ADDR_URPFFAILED 128 
 int /*<<< orphan*/  PF_ANEQ (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static int
pf_addr_wrap_neq(struct pf_addr_wrap *aw1, struct pf_addr_wrap *aw2)
{
	if (aw1->type != aw2->type)
		return (1);
	switch (aw1->type) {
	case PF_ADDR_ADDRMASK:
	case PF_ADDR_RANGE:
		if (PF_ANEQ(&aw1->v.a.addr, &aw2->v.a.addr, 0))
			return (1);
		if (PF_ANEQ(&aw1->v.a.mask, &aw2->v.a.mask, 0))
			return (1);
		return (0);
	case PF_ADDR_DYNIFTL:
		return (aw1->p.dyn == NULL || aw2->p.dyn == NULL ||
		    aw1->p.dyn->pfid_kt != aw2->p.dyn->pfid_kt);
	case PF_ADDR_NOROUTE:
	case PF_ADDR_URPFFAILED:
		return (0);
	case PF_ADDR_TABLE:
		return (aw1->p.tbl != aw2->p.tbl);
	case PF_ADDR_RTLABEL:
		return (aw1->v.rtlabel != aw2->v.rtlabel);
	default:
		printf("invalid address type: %d\n", aw1->type);
		return (1);
	}
}