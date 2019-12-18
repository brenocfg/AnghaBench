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
typedef  int /*<<< orphan*/  va_list ;
typedef  int /*<<< orphan*/  location_t ;
typedef  int /*<<< orphan*/  diagnostic_t ;
typedef  int /*<<< orphan*/  diagnostic_info ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char const*) ; 
 int /*<<< orphan*/  diagnostic_set_info_translated (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
diagnostic_set_info (diagnostic_info *diagnostic, const char *gmsgid,
		     va_list *args, location_t location,
		     diagnostic_t kind)
{
  diagnostic_set_info_translated (diagnostic, _(gmsgid), args, location, kind);
}