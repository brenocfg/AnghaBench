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
struct asn_oid {size_t len; int /*<<< orphan*/ * subs; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void
asn_append_oid(struct asn_oid *to, const struct asn_oid *from)
{
	memcpy(&to->subs[to->len], &from->subs[0],
	    from->len * sizeof(from->subs[0]));
	to->len += from->len;
}