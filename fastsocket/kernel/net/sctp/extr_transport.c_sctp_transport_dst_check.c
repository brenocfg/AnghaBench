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
struct sctp_transport {struct dst_entry* dst; } ;
struct dst_entry {TYPE_1__* ops; scalar_t__ obsolete; } ;
struct TYPE_2__ {int /*<<< orphan*/ * (* check ) (struct dst_entry*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dst_release (struct dst_entry*) ; 
 int /*<<< orphan*/ * stub1 (struct dst_entry*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dst_entry *sctp_transport_dst_check(struct sctp_transport *t)
{
	struct dst_entry *dst = t->dst;

	if (dst && dst->obsolete && dst->ops->check(dst, 0) == NULL) {
		dst_release(t->dst);
		t->dst = NULL;
		return NULL;
	}

	return dst;
}