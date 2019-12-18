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
struct p9_idpool {int /*<<< orphan*/  pool; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct p9_idpool* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  idr_init (int /*<<< orphan*/ *) ; 
 struct p9_idpool* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct p9_idpool *p9_idpool_create(void)
{
	struct p9_idpool *p;

	p = kmalloc(sizeof(struct p9_idpool), GFP_KERNEL);
	if (!p)
		return ERR_PTR(-ENOMEM);

	spin_lock_init(&p->lock);
	idr_init(&p->pool);

	return p;
}