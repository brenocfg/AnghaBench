#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ipath_portdata {int port_cnt; int port_seq_cnt; int /*<<< orphan*/ * port_pkeys; struct ipath_devdata* port_dd; } ;
struct ipath_devdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IPATH_DEFAULT_P_KEY ; 
 struct ipath_portdata* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ipath_portdata *create_portdata0(struct ipath_devdata *dd)
{
	struct ipath_portdata *pd = NULL;

	pd = kzalloc(sizeof(*pd), GFP_KERNEL);
	if (pd) {
		pd->port_dd = dd;
		pd->port_cnt = 1;
		/* The port 0 pkey table is used by the layer interface. */
		pd->port_pkeys[0] = IPATH_DEFAULT_P_KEY;
		pd->port_seq_cnt = 1;
	}
	return pd;
}