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
struct symtab_and_line {int dummy; } ;
typedef  enum exception_event_kind { ____Placeholder_exception_event_kind } exception_event_kind ;

/* Variables and functions */

struct symtab_and_line *
child_enable_exception_callback (enum exception_event_kind kind, int enable)
{
  return (struct symtab_and_line *) NULL;
}