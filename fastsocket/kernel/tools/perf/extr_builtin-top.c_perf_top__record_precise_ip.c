#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct symbol {int /*<<< orphan*/  name; } ;
struct perf_top {TYPE_2__* sym_filter_entry; } ;
struct TYPE_9__ {TYPE_4__* map; struct symbol* sym; } ;
struct hist_entry {TYPE_3__ ms; } ;
struct annotation {int /*<<< orphan*/  lock; int /*<<< orphan*/ * src; } ;
struct TYPE_10__ {int /*<<< orphan*/  erange_warned; int /*<<< orphan*/  (* map_ip ) (TYPE_4__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_7__ {struct symbol* sym; } ;
struct TYPE_8__ {TYPE_1__ ms; } ;

/* Variables and functions */
 int ERANGE ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ pthread_mutex_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ symbol__alloc_hist (struct symbol*) ; 
 struct annotation* symbol__annotation (struct symbol*) ; 
 int symbol__inc_addr_samples (struct symbol*,TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ui__warn_map_erange (TYPE_4__*,struct symbol*,int /*<<< orphan*/ ) ; 
 int use_browser ; 

__attribute__((used)) static void perf_top__record_precise_ip(struct perf_top *top,
					struct hist_entry *he,
					int counter, u64 ip)
{
	struct annotation *notes;
	struct symbol *sym;
	int err;

	if (he == NULL || he->ms.sym == NULL ||
	    ((top->sym_filter_entry == NULL ||
	      top->sym_filter_entry->ms.sym != he->ms.sym) && use_browser != 1))
		return;

	sym = he->ms.sym;
	notes = symbol__annotation(sym);

	if (pthread_mutex_trylock(&notes->lock))
		return;

	if (notes->src == NULL && symbol__alloc_hist(sym) < 0) {
		pthread_mutex_unlock(&notes->lock);
		pr_err("Not enough memory for annotating '%s' symbol!\n",
		       sym->name);
		sleep(1);
		return;
	}

	ip = he->ms.map->map_ip(he->ms.map, ip);
	err = symbol__inc_addr_samples(sym, he->ms.map, counter, ip);

	pthread_mutex_unlock(&notes->lock);

	if (err == -ERANGE && !he->ms.map->erange_warned)
		ui__warn_map_erange(he->ms.map, sym, ip);
}