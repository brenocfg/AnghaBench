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
struct TYPE_4__ {TYPE_2__* t_ardef; } ;
typedef  TYPE_1__ tdesc_t ;
struct TYPE_5__ {int /*<<< orphan*/  ad_idxtype; int /*<<< orphan*/  ad_contents; } ;
typedef  TYPE_2__ ardef_t ;

/* Variables and functions */
 int tdtraverse (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
tdtrav_array(tdesc_t *this, tdtrav_data_t *tdtd)
{
	ardef_t *ardef = this->t_ardef;
	int rc;

	if ((rc = tdtraverse(ardef->ad_contents, &ardef->ad_contents,
	    tdtd)) < 0)
		return (rc);

	return (tdtraverse(ardef->ad_idxtype, &ardef->ad_idxtype, tdtd));
}