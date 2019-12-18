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
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 TYPE_1__* current_interpreter ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

int
current_interp_named_p (const char *interp_name)
{
  if (current_interpreter)
    return (strcmp (current_interpreter->name, interp_name) == 0);

  return 0;
}