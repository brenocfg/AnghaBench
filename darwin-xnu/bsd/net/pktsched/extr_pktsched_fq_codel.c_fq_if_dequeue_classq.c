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
struct ifclassq {int dummy; } ;
typedef  int /*<<< orphan*/  classq_pkt_type_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLASSQ_DEQUEUE_MAX_BYTE_LIMIT ; 
 int /*<<< orphan*/  fq_if_dequeue_classq_multi (struct ifclassq*,int,int /*<<< orphan*/ ,void**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *
fq_if_dequeue_classq(struct ifclassq *ifq, classq_pkt_type_t *ptype)
{
	void *top;

	(void) fq_if_dequeue_classq_multi(ifq, 1,
	    CLASSQ_DEQUEUE_MAX_BYTE_LIMIT, &top, NULL, NULL, NULL, ptype);
	return (top);
}