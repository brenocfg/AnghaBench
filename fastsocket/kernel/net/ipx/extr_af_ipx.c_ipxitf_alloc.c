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
struct net_device {int dummy; } ;
struct ipx_interface {unsigned char if_internal; int if_ipx_offset; int /*<<< orphan*/  if_sklist_lock; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  if_sklist; int /*<<< orphan*/  if_sknum; struct datalink_proto* if_dlink; int /*<<< orphan*/  if_dlink_type; int /*<<< orphan*/  if_netnum; struct net_device* if_dev; } ;
struct datalink_proto {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_HLIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPX_MIN_EPHEMERAL_SOCKET ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 struct ipx_interface* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct ipx_interface *ipxitf_alloc(struct net_device *dev, __be32 netnum,
					  __be16 dlink_type,
					  struct datalink_proto *dlink,
					  unsigned char internal,
					  int ipx_offset)
{
	struct ipx_interface *intrfc = kmalloc(sizeof(*intrfc), GFP_ATOMIC);

	if (intrfc) {
		intrfc->if_dev		= dev;
		intrfc->if_netnum	= netnum;
		intrfc->if_dlink_type 	= dlink_type;
		intrfc->if_dlink 	= dlink;
		intrfc->if_internal 	= internal;
		intrfc->if_ipx_offset 	= ipx_offset;
		intrfc->if_sknum 	= IPX_MIN_EPHEMERAL_SOCKET;
		INIT_HLIST_HEAD(&intrfc->if_sklist);
		atomic_set(&intrfc->refcnt, 1);
		spin_lock_init(&intrfc->if_sklist_lock);
	}

	return intrfc;
}