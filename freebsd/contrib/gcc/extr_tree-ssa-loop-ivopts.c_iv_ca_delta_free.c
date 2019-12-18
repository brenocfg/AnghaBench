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
struct iv_ca_delta {struct iv_ca_delta* next_change; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct iv_ca_delta*) ; 

__attribute__((used)) static void
iv_ca_delta_free (struct iv_ca_delta **delta)
{
  struct iv_ca_delta *act, *next;

  for (act = *delta; act; act = next)
    {
      next = act->next_change;
      free (act);
    }

  *delta = NULL;
}