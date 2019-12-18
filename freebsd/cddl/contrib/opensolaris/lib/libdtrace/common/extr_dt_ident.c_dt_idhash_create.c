#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint_t ;
struct TYPE_5__ {char const* dh_name; int dh_hashsz; scalar_t__ dh_maxid; scalar_t__ dh_minid; scalar_t__ dh_nextid; int /*<<< orphan*/  const* dh_tmpl; } ;
typedef  TYPE_1__ dt_idhash_t ;
typedef  int /*<<< orphan*/  dt_ident_t ;

/* Variables and functions */
 int _dtrace_strbuckets ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bzero (TYPE_1__*,size_t) ; 
 TYPE_1__* malloc (size_t) ; 

dt_idhash_t *
dt_idhash_create(const char *name, const dt_ident_t *tmpl,
    uint_t min, uint_t max)
{
	dt_idhash_t *dhp;
	size_t size;

	assert(min <= max);

	size = sizeof (dt_idhash_t) +
	    sizeof (dt_ident_t *) * (_dtrace_strbuckets - 1);

	if ((dhp = malloc(size)) == NULL)
		return (NULL);

	bzero(dhp, size);
	dhp->dh_name = name;
	dhp->dh_tmpl = tmpl;
	dhp->dh_nextid = min;
	dhp->dh_minid = min;
	dhp->dh_maxid = max;
	dhp->dh_hashsz = _dtrace_strbuckets;

	return (dhp);
}