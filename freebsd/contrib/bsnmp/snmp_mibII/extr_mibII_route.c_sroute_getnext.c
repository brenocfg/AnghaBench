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
typedef  int u_int ;
struct sroute {scalar_t__* index; } ;
struct asn_oid {int len; scalar_t__* subs; } ;

/* Variables and functions */
 scalar_t__ ASN_MAXID ; 
 struct sroute* RB_LEFT (struct sroute*,int /*<<< orphan*/ ) ; 
 struct sroute* RB_MIN (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct sroute* RB_RIGHT (struct sroute*,int /*<<< orphan*/ ) ; 
 struct sroute* RB_ROOT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  link ; 
 int sroute_compare (struct sroute*,struct sroute*) ; 
 int /*<<< orphan*/  sroutes ; 

__attribute__((used)) static struct sroute *
sroute_getnext(struct asn_oid *oid, u_int sub)
{
	u_int i;
	int comp;
	struct sroute key;
	struct sroute *best;
	struct sroute *s;

	/*
	 * We now, that the OID is at least the tableEntry OID. If it is,
	 * the user wants the first route.
	 */
	if (oid->len == sub)
		return (RB_MIN(sroutes, &sroutes));

	/*
	 * This is also true for any index that consists of zeros and is
	 * shorter than the full index.
	 */
	if (oid->len < sub + 13) {
		for (i = sub; i < oid->len; i++)
			if (oid->subs[i] != 0)
				break;
		if (i == oid->len)
			return (RB_MIN(sroutes, &sroutes));

		/*
		 * Now if the index is too short, we fill it with zeros and then
		 * subtract one from the index. We can do this, because we now,
		 * that there is at least one index element that is not zero.
		 */
		for (i = oid->len; i < sub + 13; i++)
			oid->subs[i] = 0;

		for (i = sub + 13 - 1; i >= sub; i--) {
			if (oid->subs[i] != 0) {
				oid->subs[i]--;
				break;
			}
			oid->subs[i] = ASN_MAXID;
		}
		oid->len = sub + 13;
	}

	/* build the index */
	for (i = sub; i < sub + 13; i++)
		key.index[i - sub] = oid->subs[i];

	/* now find the element */
	best = NULL;
	s = RB_ROOT(&sroutes);

	while (s != NULL) {
		comp = sroute_compare(&key, s);
		if (comp >= 0) {
			/* The current element is smaller than what we search.
			 * Forget about it and move to the right subtree. */
			s = RB_RIGHT(s, link);
			continue;
		}
		/* the current element is larger than what we search.
		 * forget about the right subtree (its even larger), but
		 * the current element may be what we need. */
		if (best == NULL || sroute_compare(s, best) < 0)
			/* this one's better */
			best = s;

		s = RB_LEFT(s, link);
	}
	return (best);
}