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
struct lsap_cb {int dummy; } ;
typedef  int /*<<< orphan*/  hashbin_t ;
typedef  int /*<<< orphan*/  IRLMP_EVENT ;

/* Variables and functions */
 int /*<<< orphan*/ * hashbin_find_next (int /*<<< orphan*/ *,long,int /*<<< orphan*/ *,void*) ; 
 scalar_t__ hashbin_get_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irlmp_do_lsap_event (struct lsap_cb*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
irlmp_do_all_lsap_event(hashbin_t *	lsap_hashbin,
			IRLMP_EVENT	event)
{
	struct lsap_cb *lsap;
	struct lsap_cb *lsap_next;

	/* Note : this function use the new hashbin_find_next()
	 * function, instead of the old hashbin_get_next().
	 * This make sure that we are always pointing one lsap
	 * ahead, so that if the current lsap is removed as the
	 * result of sending the event, we don't care.
	 * Also, as we store the context ourselves, if an enumeration
	 * of the same lsap hashbin happens as the result of sending the
	 * event, we don't care.
	 * The only problem is if the next lsap is removed. In that case,
	 * hashbin_find_next() will return NULL and we will abort the
	 * enumeration. - Jean II */

	/* Also : we don't accept any skb in input. We can *NOT* pass
	 * the same skb to multiple clients safely, we would need to
	 * skb_clone() it. - Jean II */

	lsap = (struct lsap_cb *) hashbin_get_first(lsap_hashbin);

	while (NULL != hashbin_find_next(lsap_hashbin,
					 (long) lsap,
					 NULL,
					 (void *) &lsap_next) ) {
		irlmp_do_lsap_event(lsap, event, NULL);
		lsap = lsap_next;
	}
}