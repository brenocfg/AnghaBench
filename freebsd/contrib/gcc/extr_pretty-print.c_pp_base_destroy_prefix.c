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
struct TYPE_3__ {int /*<<< orphan*/ * prefix; } ;
typedef  TYPE_1__ pretty_printer ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 

void
pp_base_destroy_prefix (pretty_printer *pp)
{
  if (pp->prefix != NULL)
    {
      free ((char *) pp->prefix);
      pp->prefix = NULL;
    }
}