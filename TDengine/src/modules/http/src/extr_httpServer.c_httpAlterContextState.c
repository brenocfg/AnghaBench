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
struct TYPE_3__ {int /*<<< orphan*/  state; } ;
typedef  scalar_t__ HttpContextState ;
typedef  TYPE_1__ HttpContext ;

/* Variables and functions */
 scalar_t__ atomic_val_compare_exchange_32 (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 

bool httpAlterContextState(HttpContext *pContext, HttpContextState srcState, HttpContextState destState) {
  return (atomic_val_compare_exchange_32(&pContext->state, srcState, destState) == srcState);
}