#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct concap_proto {TYPE_1__* proto_data; scalar_t__ flags; int /*<<< orphan*/ * pops; int /*<<< orphan*/ * net_dev; int /*<<< orphan*/ * dops; int /*<<< orphan*/  lock; } ;
struct TYPE_3__ {struct concap_proto priv; int /*<<< orphan*/  state; int /*<<< orphan*/  magic; } ;
typedef  TYPE_1__ ix25_pdata_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ISDN_X25IFACE_MAGIC ; 
 int /*<<< orphan*/  IX25DEBUG (char*) ; 
 int /*<<< orphan*/  WAN_UNCONFIGURED ; 
 int /*<<< orphan*/  ix25_pops ; 
 TYPE_1__* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct concap_proto * isdn_x25iface_proto_new(void)
{
	ix25_pdata_t * tmp = kmalloc(sizeof(ix25_pdata_t),GFP_KERNEL);
	IX25DEBUG("isdn_x25iface_proto_new\n");
	if( tmp ){
		tmp -> magic = ISDN_X25IFACE_MAGIC;
		tmp -> state = WAN_UNCONFIGURED;
		/* private data space used to hold the concap_proto data.
		   Only to be accessed via the returned pointer */
		spin_lock_init(&tmp->priv.lock);
		tmp -> priv.dops       = NULL;
		tmp -> priv.net_dev    = NULL;
		tmp -> priv.pops       = &ix25_pops;
		tmp -> priv.flags      = 0;
		tmp -> priv.proto_data = tmp;
		return( &(tmp -> priv) );
	}
	return NULL;
}