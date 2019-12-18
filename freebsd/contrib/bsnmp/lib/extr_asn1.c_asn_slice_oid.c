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
typedef  size_t u_int ;
struct asn_oid {size_t len; int /*<<< orphan*/ * subs; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void
asn_slice_oid(struct asn_oid *dest, const struct asn_oid *src,
    u_int from, u_int to)
{
	if (from >= to) {
		dest->len = 0;
		return;
	}
	dest->len = to - from;
	memcpy(dest->subs, &src->subs[from], dest->len * sizeof(dest->subs[0]));
}