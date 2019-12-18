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
struct TYPE_2__ {scalar_t__ la_type_check; } ;

/* Variables and functions */
 TYPE_1__* current_language ; 
 int /*<<< orphan*/  printf_unfiltered (char*) ; 
 scalar_t__ type_check ; 

__attribute__((used)) static void
show_type_command (char *ignore, int from_tty)
{
  if (type_check != current_language->la_type_check)
    printf_unfiltered (
			"Warning: the current type check setting does not match the language.\n");
}