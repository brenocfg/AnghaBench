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
typedef  scalar_t__ utf32_t ;
struct LineBreakProperties {scalar_t__ prop; scalar_t__ start; scalar_t__ end; } ;
typedef  enum LineBreakClass { ____Placeholder_LineBreakClass } LineBreakClass ;

/* Variables and functions */
 scalar_t__ LBP_Undefined ; 
 int LBP_XX ; 

__attribute__((used)) static enum LineBreakClass get_char_lb_class(
		utf32_t ch,
		struct LineBreakProperties *lbp)
{
	while (lbp->prop != LBP_Undefined && ch >= lbp->start)
	{
		if (ch <= lbp->end)
			return lbp->prop;
		++lbp;
	}
	return LBP_XX;
}