#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cred {int /*<<< orphan*/  magic; int /*<<< orphan*/  usage; TYPE_1__* tgcred; } ;
struct TYPE_2__ {int /*<<< orphan*/  usage; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRED_MAGIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  abort_creds (struct cred*) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cred_jar ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct cred*) ; 
 struct cred* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ security_cred_alloc_blank (struct cred*,int /*<<< orphan*/ ) ; 

struct cred *cred_alloc_blank(void)
{
	struct cred *new;

	new = kmem_cache_zalloc(cred_jar, GFP_KERNEL);
	if (!new)
		return NULL;

#ifdef CONFIG_KEYS
	new->tgcred = kzalloc(sizeof(*new->tgcred), GFP_KERNEL);
	if (!new->tgcred) {
		kmem_cache_free(cred_jar, new);
		return NULL;
	}
	atomic_set(&new->tgcred->usage, 1);
#endif

	atomic_set(&new->usage, 1);

	if (security_cred_alloc_blank(new, GFP_KERNEL) < 0)
		goto error;

#ifdef CONFIG_DEBUG_CREDENTIALS
	new->magic = CRED_MAGIC;
#endif
	return new;

error:
	abort_creds(new);
	return NULL;
}