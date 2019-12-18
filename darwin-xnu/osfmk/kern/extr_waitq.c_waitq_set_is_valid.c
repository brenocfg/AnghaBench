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
struct TYPE_2__ {scalar_t__ waitq_isvalid; } ;
struct waitq_set {TYPE_1__ wqset_q; } ;

/* Variables and functions */
 scalar_t__ waitqs_is_set (struct waitq_set*) ; 

int waitq_set_is_valid(struct waitq_set *wqset)
{
	return (wqset != NULL) && wqset->wqset_q.waitq_isvalid && waitqs_is_set(wqset);
}