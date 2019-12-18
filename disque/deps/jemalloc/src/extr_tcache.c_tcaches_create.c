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
typedef  int /*<<< orphan*/  tsd_t ;
struct TYPE_5__ {int /*<<< orphan*/ * tcache; struct TYPE_5__* next; } ;
typedef  TYPE_1__ tcaches_t ;
typedef  int /*<<< orphan*/  tcache_t ;

/* Variables and functions */
 int MALLOCX_TCACHE_MAX ; 
 int /*<<< orphan*/  a0get () ; 
 TYPE_1__* base_alloc (int) ; 
 int /*<<< orphan*/ * tcache_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* tcaches ; 
 TYPE_1__* tcaches_avail ; 
 int tcaches_past ; 

bool
tcaches_create(tsd_t *tsd, unsigned *r_ind)
{
	tcache_t *tcache;
	tcaches_t *elm;

	if (tcaches == NULL) {
		tcaches = base_alloc(sizeof(tcache_t *) *
		    (MALLOCX_TCACHE_MAX+1));
		if (tcaches == NULL)
			return (true);
	}

	if (tcaches_avail == NULL && tcaches_past > MALLOCX_TCACHE_MAX)
		return (true);
	tcache = tcache_create(tsd, a0get());
	if (tcache == NULL)
		return (true);

	if (tcaches_avail != NULL) {
		elm = tcaches_avail;
		tcaches_avail = tcaches_avail->next;
		elm->tcache = tcache;
		*r_ind = elm - tcaches;
	} else {
		elm = &tcaches[tcaches_past];
		elm->tcache = tcache;
		*r_ind = tcaches_past;
		tcaches_past++;
	}

	return (false);
}