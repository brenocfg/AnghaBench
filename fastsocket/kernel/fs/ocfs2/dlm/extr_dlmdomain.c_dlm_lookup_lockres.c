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
struct dlm_lock_resource {int dummy; } ;
struct dlm_ctxt {int /*<<< orphan*/  spinlock; } ;

/* Variables and functions */
 struct dlm_lock_resource* __dlm_lookup_lockres (struct dlm_ctxt*,char const*,unsigned int,unsigned int) ; 
 unsigned int dlm_lockid_hash (char const*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

struct dlm_lock_resource * dlm_lookup_lockres(struct dlm_ctxt *dlm,
				    const char *name,
				    unsigned int len)
{
	struct dlm_lock_resource *res;
	unsigned int hash = dlm_lockid_hash(name, len);

	spin_lock(&dlm->spinlock);
	res = __dlm_lookup_lockres(dlm, name, len, hash);
	spin_unlock(&dlm->spinlock);
	return res;
}