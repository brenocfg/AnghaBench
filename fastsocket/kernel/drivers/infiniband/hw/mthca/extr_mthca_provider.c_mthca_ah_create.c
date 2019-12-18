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
struct ib_ah {int dummy; } ;
struct mthca_ah {struct ib_ah ibah; } ;
struct ib_pd {int /*<<< orphan*/  device; } ;
struct ib_ah_attr {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct ib_ah* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  kfree (struct mthca_ah*) ; 
 struct mthca_ah* kmalloc (int,int /*<<< orphan*/ ) ; 
 int mthca_create_ah (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ib_ah_attr*,struct mthca_ah*) ; 
 int /*<<< orphan*/  to_mdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_mpd (struct ib_pd*) ; 

__attribute__((used)) static struct ib_ah *mthca_ah_create(struct ib_pd *pd,
				     struct ib_ah_attr *ah_attr)
{
	int err;
	struct mthca_ah *ah;

	ah = kmalloc(sizeof *ah, GFP_ATOMIC);
	if (!ah)
		return ERR_PTR(-ENOMEM);

	err = mthca_create_ah(to_mdev(pd->device), to_mpd(pd), ah_attr, ah);
	if (err) {
		kfree(ah);
		return ERR_PTR(err);
	}

	return &ah->ibah;
}