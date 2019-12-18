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
struct devname_cache {scalar_t__ device; char* devname; int /*<<< orphan*/  rcu; } ;
struct block_device {int dummy; } ;
typedef  scalar_t__ dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  CACHE_SIZE_BITS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  __bdevname (scalar_t__,char*) ; 
 int /*<<< orphan*/  bdevname (struct block_device*,char*) ; 
 struct block_device* bdget (scalar_t__) ; 
 int /*<<< orphan*/  bdput (struct block_device*) ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct devname_cache** devcache ; 
 int /*<<< orphan*/  devname_cache_lock ; 
 int /*<<< orphan*/  free_devcache ; 
 int hash_32 (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct devname_cache*) ; 
 struct devname_cache* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

const char *jbd2_dev_to_name(dev_t device)
{
	int	i = hash_32(device, CACHE_SIZE_BITS);
	char	*ret;
	struct block_device *bd;
	static struct devname_cache *new_dev;

	rcu_read_lock();
	if (devcache[i] && devcache[i]->device == device) {
		ret = devcache[i]->devname;
		rcu_read_unlock();
		return ret;
	}
	rcu_read_unlock();

	new_dev = kmalloc(sizeof(struct devname_cache), GFP_KERNEL);
	if (!new_dev)
		return "NODEV-ALLOCFAILURE"; /* Something non-NULL */
	spin_lock(&devname_cache_lock);
	if (devcache[i]) {
		if (devcache[i]->device == device) {
			kfree(new_dev);
			ret = devcache[i]->devname;
			spin_unlock(&devname_cache_lock);
			return ret;
		}
		call_rcu(&devcache[i]->rcu, free_devcache);
	}
	devcache[i] = new_dev;
	devcache[i]->device = device;
	bd = bdget(device);
	if (bd) {
		bdevname(bd, devcache[i]->devname);
		bdput(bd);
	} else
		__bdevname(device, devcache[i]->devname);
	ret = devcache[i]->devname;
	spin_unlock(&devname_cache_lock);
	return ret;
}