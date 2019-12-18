#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tdtrav_data_t ;
struct TYPE_4__ {TYPE_2__* t_members; } ;
typedef  TYPE_1__ tdesc_t ;
struct TYPE_5__ {int /*<<< orphan*/  ml_type; struct TYPE_5__* ml_next; } ;
typedef  TYPE_2__ mlist_t ;

/* Variables and functions */
 int tdtraverse (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
tdtrav_su(tdesc_t *this, tdtrav_data_t *tdtd)
{
	mlist_t *ml;
	int rc = 0;

	for (ml = this->t_members; ml; ml = ml->ml_next) {
		if ((rc = tdtraverse(ml->ml_type, &ml->ml_type, tdtd)) < 0)
			return (rc);
	}

	return (rc);
}