#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  offset; } ;
struct TYPE_4__ {TYPE_1__ target; } ;
struct disasm_line {TYPE_2__ ops; int /*<<< orphan*/  ins; } ;
struct annotate_browser {struct disasm_line* selection; } ;
typedef  int /*<<< orphan*/  s64 ;

/* Variables and functions */
 struct disasm_line* annotate_browser__find_offset (struct annotate_browser*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  annotate_browser__set_top (struct annotate_browser*,struct disasm_line*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ins__is_jump (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ui_helpline__puts (char*) ; 

__attribute__((used)) static bool annotate_browser__jump(struct annotate_browser *browser)
{
	struct disasm_line *dl = browser->selection;
	s64 idx;

	if (!ins__is_jump(dl->ins))
		return false;

	dl = annotate_browser__find_offset(browser, dl->ops.target.offset, &idx);
	if (dl == NULL) {
		ui_helpline__puts("Invallid jump offset");
		return true;
	}

	annotate_browser__set_top(browser, dl, idx);
	
	return true;
}