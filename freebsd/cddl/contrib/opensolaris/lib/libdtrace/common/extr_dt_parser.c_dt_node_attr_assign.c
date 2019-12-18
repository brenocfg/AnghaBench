#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  s ;
typedef  int /*<<< orphan*/  dtrace_attribute_t ;
struct TYPE_6__ {int /*<<< orphan*/  dn_attr; } ;
typedef  TYPE_1__ dt_node_t ;
typedef  int /*<<< orphan*/  a ;
struct TYPE_7__ {int pcb_cflags; int /*<<< orphan*/  pcb_amin; } ;

/* Variables and functions */
 int BUFSIZ ; 
 int DTRACE_ATTR2STR_MAX ; 
 int DTRACE_C_EATTR ; 
 int /*<<< orphan*/  D_ATTR_MIN ; 
 int /*<<< orphan*/  dnerror (TYPE_1__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dt_attr_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_node_name (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  dtrace_attr2str (int /*<<< orphan*/ ,char*,int) ; 
 TYPE_2__* yypcb ; 

void
dt_node_attr_assign(dt_node_t *dnp, dtrace_attribute_t attr)
{
	if ((yypcb->pcb_cflags & DTRACE_C_EATTR) &&
	    (dt_attr_cmp(attr, yypcb->pcb_amin) < 0)) {
		char a[DTRACE_ATTR2STR_MAX];
		char s[BUFSIZ];

		dnerror(dnp, D_ATTR_MIN, "attributes for %s (%s) are less than "
		    "predefined minimum\n", dt_node_name(dnp, s, sizeof (s)),
		    dtrace_attr2str(attr, a, sizeof (a)));
	}

	dnp->dn_attr = attr;
}