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
struct TYPE_4__ {int td_nextid; int td_curvgen; int /*<<< orphan*/  td_mergelock; void* td_iihash; void* td_idhash; void* td_layouthash; } ;
typedef  TYPE_1__ tdata_t ;

/* Variables and functions */
 int /*<<< orphan*/  IIDESC_HASH_SIZE ; 
 int /*<<< orphan*/  TDATA_ID_HASH_SIZE ; 
 int /*<<< orphan*/  TDATA_LAYOUT_HASH_SIZE ; 
 void* hash_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iidesc_hash ; 
 int /*<<< orphan*/  pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * tdesc_idcmp ; 
 int /*<<< orphan*/  tdesc_idhash ; 
 int /*<<< orphan*/ * tdesc_layoutcmp ; 
 int /*<<< orphan*/  tdesc_layouthash ; 
 TYPE_1__* xcalloc (int) ; 

tdata_t *
tdata_new(void)
{
	tdata_t *new = xcalloc(sizeof (tdata_t));

	new->td_layouthash = hash_new(TDATA_LAYOUT_HASH_SIZE, tdesc_layouthash,
	    tdesc_layoutcmp);
	new->td_idhash = hash_new(TDATA_ID_HASH_SIZE, tdesc_idhash,
	    tdesc_idcmp);
	/*
	 * This is also traversed as a list, but amortized O(1)
	 * lookup massively impacts part of the merge phase, so
	 * we store the iidescs as a hash.
	 */
	new->td_iihash = hash_new(IIDESC_HASH_SIZE, iidesc_hash, NULL);
	new->td_nextid = 1;
	new->td_curvgen = 1;

	pthread_mutex_init(&new->td_mergelock, NULL);

	return (new);
}