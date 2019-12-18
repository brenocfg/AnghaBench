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
struct exception_event_record {int dummy; } ;

/* Variables and functions */

struct exception_event_record *
child_get_current_exception_event (void)
{
  return (struct exception_event_record *) NULL;
}