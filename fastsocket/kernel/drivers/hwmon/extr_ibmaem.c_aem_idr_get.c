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

/* Variables and functions */
 int EAGAIN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MAX_ID_MASK ; 
 int /*<<< orphan*/  aem_idr ; 
 int /*<<< orphan*/  aem_idr_lock ; 
 int idr_get_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  idr_pre_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int aem_idr_get(int *id)
{
	int i, err;

again:
	if (unlikely(!idr_pre_get(&aem_idr, GFP_KERNEL)))
		return -ENOMEM;

	spin_lock(&aem_idr_lock);
	err = idr_get_new(&aem_idr, NULL, &i);
	spin_unlock(&aem_idr_lock);

	if (unlikely(err == -EAGAIN))
		goto again;
	else if (unlikely(err))
		return err;

	*id = i & MAX_ID_MASK;
	return 0;
}