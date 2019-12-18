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
struct secashead {int /*<<< orphan*/ * savtree; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int M_NOWAIT ; 
 int /*<<< orphan*/  M_SECA ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 scalar_t__ _MALLOC (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sadb_mutex ; 

struct secashead *
keydb_newsecashead(void)
{
	struct secashead *p;
	int i;

	LCK_MTX_ASSERT(sadb_mutex, LCK_MTX_ASSERT_OWNED);

	p = (struct secashead *)_MALLOC(sizeof(*p), M_SECA, M_NOWAIT | M_ZERO);
	if (!p) {
		lck_mtx_unlock(sadb_mutex);
		p = (struct secashead *)_MALLOC(sizeof(*p), M_SECA,
		    M_WAITOK | M_ZERO);
		lck_mtx_lock(sadb_mutex);
	}
	if (!p) 
		return p;
	for (i = 0; i < sizeof(p->savtree)/sizeof(p->savtree[0]); i++)
		LIST_INIT(&p->savtree[i]);
	return p;
}