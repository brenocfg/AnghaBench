#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  va_list ;
typedef  int /*<<< orphan*/  location_t ;
typedef  int /*<<< orphan*/  diagnostic_t ;
struct TYPE_4__ {char const* format_spec; int /*<<< orphan*/ * args_ptr; int /*<<< orphan*/  err_no; } ;
struct TYPE_5__ {scalar_t__ option_index; int /*<<< orphan*/  kind; int /*<<< orphan*/  location; TYPE_1__ message; } ;
typedef  TYPE_2__ diagnostic_info ;

/* Variables and functions */
 int /*<<< orphan*/  errno ; 

void
diagnostic_set_info_translated (diagnostic_info *diagnostic, const char *msg,
				va_list *args, location_t location,
				diagnostic_t kind)
{
  diagnostic->message.err_no = errno;
  diagnostic->message.args_ptr = args;
  diagnostic->message.format_spec = msg;
  diagnostic->location = location;
  diagnostic->kind = kind;
  diagnostic->option_index = 0;
}