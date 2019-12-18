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
struct map_symbol {TYPE_4__* map; struct symbol* sym; } ;
struct hist_browser_timer {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  addr; } ;
struct TYPE_8__ {TYPE_1__ target; } ;
struct disasm_line {TYPE_2__ ops; int /*<<< orphan*/  ins; } ;
struct annotation {int /*<<< orphan*/  lock; int /*<<< orphan*/ * src; } ;
struct TYPE_9__ {struct map_symbol* priv; } ;
struct annotate_browser {TYPE_3__ b; struct disasm_line* selection; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* map_ip ) (TYPE_4__*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ins__is_call (int /*<<< orphan*/ ) ; 
 struct symbol* map__find_symbol (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ symbol__alloc_hist (struct symbol*) ; 
 struct annotation* symbol__annotation (struct symbol*) ; 
 int /*<<< orphan*/  symbol__tui_annotate (struct symbol*,TYPE_4__*,int,struct hist_browser_timer*) ; 
 int /*<<< orphan*/  ui__warning (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ui_browser__show_title (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ui_helpline__puts (char*) ; 

__attribute__((used)) static bool annotate_browser__callq(struct annotate_browser *browser, int evidx,
				    struct hist_browser_timer *hbt)
{
	struct map_symbol *ms = browser->b.priv;
	struct disasm_line *dl = browser->selection;
	struct symbol *sym = ms->sym;
	struct annotation *notes;
	struct symbol *target;
	u64 ip;

	if (!ins__is_call(dl->ins))
		return false;

	ip = ms->map->map_ip(ms->map, dl->ops.target.addr);
	target = map__find_symbol(ms->map, ip, NULL);
	if (target == NULL) {
		ui_helpline__puts("The called function was not found.");
		return true;
	}

	notes = symbol__annotation(target);
	pthread_mutex_lock(&notes->lock);

	if (notes->src == NULL && symbol__alloc_hist(target) < 0) {
		pthread_mutex_unlock(&notes->lock);
		ui__warning("Not enough memory for annotating '%s' symbol!\n",
			    target->name);
		return true;
	}

	pthread_mutex_unlock(&notes->lock);
	symbol__tui_annotate(target, ms->map, evidx, hbt);
	ui_browser__show_title(&browser->b, sym->name);
	return true;
}