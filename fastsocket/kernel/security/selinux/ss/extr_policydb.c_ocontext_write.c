#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct policydb_compat_info {unsigned int ocon_num; } ;
struct policydb {struct ocontext** ocontexts; } ;
struct TYPE_9__ {int /*<<< orphan*/ * mask; int /*<<< orphan*/ * addr; } ;
struct TYPE_7__ {int /*<<< orphan*/  mask; int /*<<< orphan*/  addr; } ;
struct TYPE_6__ {size_t protocol; size_t low_port; size_t high_port; } ;
struct TYPE_10__ {TYPE_4__ node6; int /*<<< orphan*/ * name; TYPE_2__ node; TYPE_1__ port; } ;
struct TYPE_8__ {size_t behavior; } ;
struct ocontext {size_t* sid; int /*<<< orphan*/ * context; TYPE_5__ u; TYPE_3__ v; struct ocontext* next; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
#define  OCON_FS 134 
#define  OCON_FSUSE 133 
#define  OCON_ISID 132 
#define  OCON_NETIF 131 
#define  OCON_NODE 130 
#define  OCON_NODE6 129 
#define  OCON_PORT 128 
 unsigned int context_write (struct policydb*,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  cpu_to_le32 (size_t) ; 
 unsigned int put_entry (int /*<<< orphan*/ *,int,int,void*) ; 
 size_t strlen (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ocontext_write(struct policydb *p, struct policydb_compat_info *info,
			  void *fp)
{
	unsigned int i, j, rc;
	size_t nel, len;
	__le32 buf[3];
	u32 nodebuf[8];
	struct ocontext *c;
	for (i = 0; i < info->ocon_num; i++) {
		nel = 0;
		for (c = p->ocontexts[i]; c; c = c->next)
			nel++;
		buf[0] = cpu_to_le32(nel);
		rc = put_entry(buf, sizeof(u32), 1, fp);
		if (rc)
			return rc;
		for (c = p->ocontexts[i]; c; c = c->next) {
			switch (i) {
			case OCON_ISID:
				buf[0] = cpu_to_le32(c->sid[0]);
				rc = put_entry(buf, sizeof(u32), 1, fp);
				if (rc)
					return rc;
				rc = context_write(p, &c->context[0], fp);
				if (rc)
					return rc;
				break;
			case OCON_FS:
			case OCON_NETIF:
				len = strlen(c->u.name);
				buf[0] = cpu_to_le32(len);
				rc = put_entry(buf, sizeof(u32), 1, fp);
				if (rc)
					return rc;
				rc = put_entry(c->u.name, 1, len, fp);
				if (rc)
					return rc;
				rc = context_write(p, &c->context[0], fp);
				if (rc)
					return rc;
				rc = context_write(p, &c->context[1], fp);
				if (rc)
					return rc;
				break;
			case OCON_PORT:
				buf[0] = cpu_to_le32(c->u.port.protocol);
				buf[1] = cpu_to_le32(c->u.port.low_port);
				buf[2] = cpu_to_le32(c->u.port.high_port);
				rc = put_entry(buf, sizeof(u32), 3, fp);
				if (rc)
					return rc;
				rc = context_write(p, &c->context[0], fp);
				if (rc)
					return rc;
				break;
			case OCON_NODE:
				nodebuf[0] = c->u.node.addr; /* network order */
				nodebuf[1] = c->u.node.mask; /* network order */
				rc = put_entry(nodebuf, sizeof(u32), 2, fp);
				if (rc)
					return rc;
				rc = context_write(p, &c->context[0], fp);
				if (rc)
					return rc;
				break;
			case OCON_FSUSE:
				buf[0] = cpu_to_le32(c->v.behavior);
				len = strlen(c->u.name);
				buf[1] = cpu_to_le32(len);
				rc = put_entry(buf, sizeof(u32), 2, fp);
				if (rc)
					return rc;
				rc = put_entry(c->u.name, 1, len, fp);
				if (rc)
					return rc;
				rc = context_write(p, &c->context[0], fp);
				if (rc)
					return rc;
				break;
			case OCON_NODE6:
				for (j = 0; j < 4; j++)
					nodebuf[j] = c->u.node6.addr[j]; /* network order */
				for (j = 0; j < 4; j++)
					nodebuf[j + 4] = c->u.node6.mask[j]; /* network order */
				rc = put_entry(nodebuf, sizeof(u32), 8, fp);
				if (rc)
					return rc;
				rc = context_write(p, &c->context[0], fp);
				if (rc)
					return rc;
				break;
			}
		}
	}
	return 0;
}