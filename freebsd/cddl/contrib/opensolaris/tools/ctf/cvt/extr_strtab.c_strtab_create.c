#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int str_hashsz; int str_nstrs; int str_size; int /*<<< orphan*/ * str_ptr; int /*<<< orphan*/  str_bufsz; scalar_t__ str_nbufs; int /*<<< orphan*/ * str_bufs; int /*<<< orphan*/  str_hash; } ;
typedef  TYPE_1__ strtab_t ;
typedef  int /*<<< orphan*/  strhash_t ;

/* Variables and functions */
 int /*<<< orphan*/  STRTAB_BUFSZ ; 
 int STRTAB_HASHSZ ; 
 int /*<<< orphan*/  strtab_grow (TYPE_1__*) ; 
 int /*<<< orphan*/  xcalloc (int) ; 

void
strtab_create(strtab_t *sp)
{
	sp->str_hash = xcalloc(STRTAB_HASHSZ * sizeof (strhash_t *));
	sp->str_hashsz = STRTAB_HASHSZ;
	sp->str_bufs = NULL;
	sp->str_ptr = NULL;
	sp->str_nbufs = 0;
	sp->str_bufsz = STRTAB_BUFSZ;
	sp->str_nstrs = 1;
	sp->str_size = 1;

	strtab_grow(sp);
	*sp->str_ptr++ = '\0';
}