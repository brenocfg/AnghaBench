#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ utf32_t ;
typedef  enum LineBreakClass { ____Placeholder_LineBreakClass } LineBreakClass ;
struct TYPE_2__ {scalar_t__ end; int /*<<< orphan*/  lbp; } ;

/* Variables and functions */
 size_t LINEBREAK_INDEX_SIZE ; 
 int /*<<< orphan*/  assert (int) ; 
 int get_char_lb_class (scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_1__* lb_prop_index ; 

__attribute__((used)) static enum LineBreakClass get_char_lb_class_default(
		utf32_t ch)
{
	size_t i = 0;
	while (ch > lb_prop_index[i].end)
		++i;
	assert(i < LINEBREAK_INDEX_SIZE);
	return get_char_lb_class(ch, lb_prop_index[i].lbp);
}