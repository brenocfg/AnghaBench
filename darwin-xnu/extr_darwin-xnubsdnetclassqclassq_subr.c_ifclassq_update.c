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
typedef  int /*<<< orphan*/  cqev_t ;

/* Variables and functions */
 int /*<<< orphan*/  IFCQ_IS_READY (struct ifclassq*) ; 
 int /*<<< orphan*/  IFCQ_LOCK_ASSERT_HELD (struct ifclassq*) ; 
 int /*<<< orphan*/  IFCQ_UPDATE (struct ifclassq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 

void
ifclassq_update(struct ifclassq *ifq, cqev_t ev)
{
	IFCQ_LOCK_ASSERT_HELD(ifq);
	VERIFY(IFCQ_IS_READY(ifq));
	IFCQ_UPDATE(ifq, ev);
}