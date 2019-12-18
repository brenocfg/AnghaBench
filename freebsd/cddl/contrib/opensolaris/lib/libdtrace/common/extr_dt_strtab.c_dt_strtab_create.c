#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint_t ;
struct TYPE_7__ {size_t str_bufsz; int str_nstrs; int str_size; int /*<<< orphan*/ * str_ptr; scalar_t__ str_nbufs; int /*<<< orphan*/ * str_bufs; int /*<<< orphan*/  str_hashsz; int /*<<< orphan*/ * str_hash; } ;
typedef  TYPE_1__ dt_strtab_t ;
typedef  int /*<<< orphan*/  dt_strhash_t ;

/* Variables and functions */
 int /*<<< orphan*/  _dtrace_strbuckets ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 
 int /*<<< orphan*/ * calloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dt_strtab_destroy (TYPE_1__*) ; 
 int dt_strtab_grow (TYPE_1__*) ; 
 TYPE_1__* malloc (int) ; 

dt_strtab_t *
dt_strtab_create(size_t bufsz)
{
	dt_strtab_t *sp = malloc(sizeof (dt_strtab_t));
	uint_t nbuckets = _dtrace_strbuckets;

	assert(bufsz != 0);

	if (sp == NULL)
		return (NULL);

	bzero(sp, sizeof (dt_strtab_t));
	sp->str_hash = calloc(nbuckets, sizeof (dt_strhash_t *));

	if (sp->str_hash == NULL)
		goto err;

	sp->str_hashsz = nbuckets;
	sp->str_bufs = NULL;
	sp->str_ptr = NULL;
	sp->str_nbufs = 0;
	sp->str_bufsz = bufsz;
	sp->str_nstrs = 1;
	sp->str_size = 1;

	if (dt_strtab_grow(sp) == -1)
		goto err;

	*sp->str_ptr++ = '\0';
	return (sp);

err:
	dt_strtab_destroy(sp);
	return (NULL);
}