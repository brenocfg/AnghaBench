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
struct nf_conn {int /*<<< orphan*/  timeout; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  death_by_timeout (unsigned long) ; 
 scalar_t__ del_timer (int /*<<< orphan*/ *) ; 
 struct nf_conn* get_next_corpse (struct net*,int (*) (struct nf_conn*,void*),void*,unsigned int*) ; 
 int /*<<< orphan*/  nf_ct_put (struct nf_conn*) ; 

void nf_ct_iterate_cleanup(struct net *net,
			   int (*iter)(struct nf_conn *i, void *data),
			   void *data)
{
	struct nf_conn *ct;
	unsigned int bucket = 0;

	while ((ct = get_next_corpse(net, iter, data, &bucket)) != NULL) {
		/* Time to push up daises... */
		if (del_timer(&ct->timeout))
			death_by_timeout((unsigned long)ct);
		/* ... else the timer will get him soon. */

		nf_ct_put(ct);
	}
}