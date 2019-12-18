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
struct xt_rateinfo {int burst; int avg; scalar_t__ cost; scalar_t__ credit_cap; struct xt_limit_priv* master; } ;
struct xt_mtchk_param {struct xt_rateinfo* matchinfo; } ;
struct xt_limit_priv {scalar_t__ credit; int /*<<< orphan*/  prev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  jiffies ; 
 struct xt_limit_priv* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,int,int) ; 
 scalar_t__ user2credits (int) ; 

__attribute__((used)) static bool limit_mt_check(const struct xt_mtchk_param *par)
{
	struct xt_rateinfo *r = par->matchinfo;
	struct xt_limit_priv *priv;

	/* Check for overflow. */
	if (r->burst == 0
	    || user2credits(r->avg * r->burst) < user2credits(r->avg)) {
		printk("Overflow in xt_limit, try lower: %u/%u\n",
		       r->avg, r->burst);
		return false;
	}

	priv = kmalloc(sizeof(*priv), GFP_KERNEL);
	if (priv == NULL)
		return false;

	/* For SMP, we only want to use one set of state. */
	r->master = priv;
	if (r->cost == 0) {
		/* User avg in seconds * XT_LIMIT_SCALE: convert to jiffies *
		   128. */
		priv->prev = jiffies;
		priv->credit = user2credits(r->avg * r->burst); /* Credits full. */
		r->credit_cap = user2credits(r->avg * r->burst); /* Credits full. */
		r->cost = user2credits(r->avg);
	}
	return true;
}