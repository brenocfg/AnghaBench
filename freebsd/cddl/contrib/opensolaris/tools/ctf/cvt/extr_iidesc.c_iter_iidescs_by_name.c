#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmpdesc ;
struct TYPE_6__ {int /*<<< orphan*/  td_iihash; } ;
typedef  TYPE_1__ tdata_t ;
struct TYPE_7__ {int /*<<< orphan*/  ii_name; } ;
typedef  TYPE_2__ iidesc_t ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (TYPE_2__*,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash_match (int /*<<< orphan*/ ,TYPE_2__*,int (*) (void*,void*),void*) ; 
 int /*<<< orphan*/  xstrdup (char const*) ; 

void
iter_iidescs_by_name(tdata_t *td, char const *name,
    int (*func)(void *, void *), void *data)
{
	iidesc_t tmpdesc;
	bzero(&tmpdesc, sizeof(tmpdesc));
	tmpdesc.ii_name = xstrdup(name);
	(void) hash_match(td->td_iihash, &tmpdesc, func, data);
	free(tmpdesc.ii_name);
}