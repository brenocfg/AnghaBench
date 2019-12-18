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
struct mlist {int dummy; } ;
struct magic_set {int /*<<< orphan*/ ** mlist; } ;
struct magic_map {int dummy; } ;
struct magic {int dummy; } ;

/* Variables and functions */
 size_t MAGIC_SETS ; 
 int add_mlist (int /*<<< orphan*/ *,struct magic_map*,size_t) ; 
 struct magic_map* apprentice_buf (struct magic_set*,struct magic*,size_t) ; 
 int /*<<< orphan*/  file_oomem (struct magic_set*,int) ; 
 int /*<<< orphan*/  file_reset (struct magic_set*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_file_tables () ; 
 int /*<<< orphan*/ * mlist_alloc () ; 
 int /*<<< orphan*/  mlist_free (int /*<<< orphan*/ *) ; 

int
buffer_apprentice(struct magic_set *ms, struct magic **bufs,
    size_t *sizes, size_t nbufs)
{
	size_t i, j;
	struct mlist *ml;
	struct magic_map *map;

	if (nbufs == 0)
		return -1;

	(void)file_reset(ms, 0);

	init_file_tables();

	for (i = 0; i < MAGIC_SETS; i++) {
		mlist_free(ms->mlist[i]);
		if ((ms->mlist[i] = mlist_alloc()) == NULL) {
			file_oomem(ms, sizeof(*ms->mlist[i]));
			goto fail;
		}
	}

	for (i = 0; i < nbufs; i++) {
		map = apprentice_buf(ms, bufs[i], sizes[i]);
		if (map == NULL)
			goto fail;

		for (j = 0; j < MAGIC_SETS; j++) {
			if (add_mlist(ms->mlist[j], map, j) == -1) {
				file_oomem(ms, sizeof(*ml));
				goto fail;
			}
		}
	}

	return 0;
fail:
	for (i = 0; i < MAGIC_SETS; i++) {
		mlist_free(ms->mlist[i]);
		ms->mlist[i] = NULL;
	}
	return -1;
}