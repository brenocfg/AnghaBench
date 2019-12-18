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
struct ipt_clusterip_tgt_info {int /*<<< orphan*/  hash_initval; int /*<<< orphan*/  hash_mode; int /*<<< orphan*/  num_total_nodes; int /*<<< orphan*/  clustermac; } ;
struct clusterip_config {int /*<<< orphan*/  list; int /*<<< orphan*/  pde; int /*<<< orphan*/  entries; int /*<<< orphan*/  refcount; int /*<<< orphan*/  hash_initval; int /*<<< orphan*/  hash_mode; int /*<<< orphan*/  num_total_nodes; int /*<<< orphan*/  clustermac; int /*<<< orphan*/  clusterip; struct net_device* dev; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int S_IRUSR ; 
 int S_IWUSR ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  clusterip_config_init_nodelist (struct clusterip_config*,struct ipt_clusterip_tgt_info const*) ; 
 int /*<<< orphan*/  clusterip_configs ; 
 int /*<<< orphan*/  clusterip_lock ; 
 int /*<<< orphan*/  clusterip_proc_fops ; 
 int /*<<< orphan*/  clusterip_procdir ; 
 int /*<<< orphan*/  kfree (struct clusterip_config*) ; 
 struct clusterip_config* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_create_data (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct clusterip_config*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct clusterip_config *
clusterip_config_init(const struct ipt_clusterip_tgt_info *i, __be32 ip,
			struct net_device *dev)
{
	struct clusterip_config *c;

	c = kzalloc(sizeof(*c), GFP_ATOMIC);
	if (!c)
		return NULL;

	c->dev = dev;
	c->clusterip = ip;
	memcpy(&c->clustermac, &i->clustermac, ETH_ALEN);
	c->num_total_nodes = i->num_total_nodes;
	clusterip_config_init_nodelist(c, i);
	c->hash_mode = i->hash_mode;
	c->hash_initval = i->hash_initval;
	atomic_set(&c->refcount, 1);
	atomic_set(&c->entries, 1);

#ifdef CONFIG_PROC_FS
	{
		char buffer[16];

		/* create proc dir entry */
		sprintf(buffer, "%pI4", &ip);
		c->pde = proc_create_data(buffer, S_IWUSR|S_IRUSR,
					  clusterip_procdir,
					  &clusterip_proc_fops, c);
		if (!c->pde) {
			kfree(c);
			return NULL;
		}
	}
#endif

	write_lock_bh(&clusterip_lock);
	list_add(&c->list, &clusterip_configs);
	write_unlock_bh(&clusterip_lock);

	return c;
}