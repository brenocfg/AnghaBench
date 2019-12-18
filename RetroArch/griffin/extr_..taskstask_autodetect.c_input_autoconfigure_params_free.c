#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * autoconfig_directory; int /*<<< orphan*/ * name; } ;
typedef  TYPE_1__ autoconfig_params_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  string_is_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void input_autoconfigure_params_free(autoconfig_params_t *params)
{
   if (!params)
      return;
   if (!string_is_empty(params->name))
      free(params->name);
   if (!string_is_empty(params->autoconfig_directory))
      free(params->autoconfig_directory);
   params->name                 = NULL;
   params->autoconfig_directory = NULL;
}