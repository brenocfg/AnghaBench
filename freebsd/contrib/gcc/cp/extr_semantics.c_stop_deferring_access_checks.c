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
struct TYPE_2__ {int /*<<< orphan*/  deferring_access_checks_kind; } ;

/* Variables and functions */
 TYPE_1__* VEC_last (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  deferred_access ; 
 int /*<<< orphan*/  deferred_access_no_check ; 
 int /*<<< orphan*/  deferred_access_stack ; 
 int /*<<< orphan*/  dk_no_deferred ; 

void
stop_deferring_access_checks (void)
{
  if (!deferred_access_no_check)
    VEC_last (deferred_access, deferred_access_stack)
      ->deferring_access_checks_kind = dk_no_deferred;
}