#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* param; } ;
struct TYPE_5__ {scalar_t__ i64Key; scalar_t__ nType; } ;
typedef  TYPE_2__ SQLFunctionCtx ;

/* Variables and functions */
 int /*<<< orphan*/  function_setup (TYPE_2__*) ; 

__attribute__((used)) static bool first_last_function_setup(SQLFunctionCtx *pCtx) {
  if (!function_setup(pCtx)) {
    return false;
  }

  // used to keep the timestamp for comparison
  pCtx->param[1].nType = 0;
  pCtx->param[1].i64Key = 0;

  return true;
}