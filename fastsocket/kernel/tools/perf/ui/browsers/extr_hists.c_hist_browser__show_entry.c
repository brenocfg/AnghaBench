#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct perf_hpp {char* buf; int size; double* ptr; } ;
struct hist_entry {scalar_t__ row_offset; int /*<<< orphan*/  sorted_chain; int /*<<< orphan*/  ms; } ;
struct TYPE_7__ {int width; unsigned short height; int /*<<< orphan*/  navkeypressed; } ;
struct hist_browser {struct hist_entry* he_selection; TYPE_1__ b; int /*<<< orphan*/  hists; int /*<<< orphan*/ * selection; } ;
typedef  int /*<<< orphan*/  s ;
typedef  scalar_t__ off_t ;
struct TYPE_9__ {scalar_t__ (* entry ) (struct perf_hpp*,struct hist_entry*) ;scalar_t__ (* color ) (struct perf_hpp*,struct hist_entry*) ;int /*<<< orphan*/  cond; } ;
struct TYPE_8__ {scalar_t__ use_callchain; } ;

/* Variables and functions */
 int /*<<< orphan*/  HE_COLORSET_NORMAL ; 
 int PERF_HPP__MAX_INDEX ; 
 int PERF_HPP__OVERHEAD ; 
 scalar_t__ hist_browser__show_callchain (struct hist_browser*,int /*<<< orphan*/ *,int,unsigned short,scalar_t__*,int*) ; 
 char hist_entry__folded (struct hist_entry*) ; 
 int /*<<< orphan*/  hist_entry__init_have_children (struct hist_entry*) ; 
 int /*<<< orphan*/  hist_entry__sort_snprintf (struct hist_entry*,char*,int,int /*<<< orphan*/ ) ; 
 TYPE_6__* perf_hpp__format ; 
 int /*<<< orphan*/  slsmg_printf (char*,...) ; 
 int /*<<< orphan*/  slsmg_write_nstring (char*,int) ; 
 scalar_t__ stub1 (struct perf_hpp*,struct hist_entry*) ; 
 scalar_t__ stub2 (struct perf_hpp*,struct hist_entry*) ; 
 TYPE_5__ symbol_conf ; 
 int /*<<< orphan*/  ui_browser__gotorc (TYPE_1__*,unsigned short,int /*<<< orphan*/ ) ; 
 int ui_browser__is_current_entry (TYPE_1__*,unsigned short) ; 
 int /*<<< orphan*/  ui_browser__set_color (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ui_browser__set_percent_color (TYPE_1__*,double,int) ; 

__attribute__((used)) static int hist_browser__show_entry(struct hist_browser *browser,
				    struct hist_entry *entry,
				    unsigned short row)
{
	char s[256];
	double percent;
	int i, printed = 0;
	int width = browser->b.width;
	char folded_sign = ' ';
	bool current_entry = ui_browser__is_current_entry(&browser->b, row);
	off_t row_offset = entry->row_offset;
	bool first = true;

	if (current_entry) {
		browser->he_selection = entry;
		browser->selection = &entry->ms;
	}

	if (symbol_conf.use_callchain) {
		hist_entry__init_have_children(entry);
		folded_sign = hist_entry__folded(entry);
	}

	if (row_offset == 0) {
		struct perf_hpp hpp = {
			.buf		= s,
			.size		= sizeof(s),
		};

		ui_browser__gotorc(&browser->b, row, 0);

		for (i = 0; i < PERF_HPP__MAX_INDEX; i++) {
			if (!perf_hpp__format[i].cond)
				continue;

			if (!first) {
				slsmg_printf("  ");
				width -= 2;
			}
			first = false;

			if (perf_hpp__format[i].color) {
				hpp.ptr = &percent;
				/* It will set percent for us. See HPP__COLOR_FN above. */
				width -= perf_hpp__format[i].color(&hpp, entry);

				ui_browser__set_percent_color(&browser->b, percent, current_entry);

				if (i == PERF_HPP__OVERHEAD && symbol_conf.use_callchain) {
					slsmg_printf("%c ", folded_sign);
					width -= 2;
				}

				slsmg_printf("%s", s);

				if (!current_entry || !browser->b.navkeypressed)
					ui_browser__set_color(&browser->b, HE_COLORSET_NORMAL);
			} else {
				width -= perf_hpp__format[i].entry(&hpp, entry);
				slsmg_printf("%s", s);
			}
		}

		/* The scroll bar isn't being used */
		if (!browser->b.navkeypressed)
			width += 1;

		hist_entry__sort_snprintf(entry, s, sizeof(s), browser->hists);
		slsmg_write_nstring(s, width);
		++row;
		++printed;
	} else
		--row_offset;

	if (folded_sign == '-' && row != browser->b.height) {
		printed += hist_browser__show_callchain(browser, &entry->sorted_chain,
							1, row, &row_offset,
							&current_entry);
		if (current_entry)
			browser->he_selection = entry;
	}

	return printed;
}