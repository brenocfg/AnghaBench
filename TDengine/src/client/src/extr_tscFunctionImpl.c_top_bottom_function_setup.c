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
typedef  int /*<<< orphan*/  STopBotInfo ;
typedef  int /*<<< orphan*/  SQLFunctionCtx ;

/* Variables and functions */
 int /*<<< orphan*/  buildTopBotStruct (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  function_setup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * getTopBotOutputInfo (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool top_bottom_function_setup(SQLFunctionCtx *pCtx) {
  if (!function_setup(pCtx)) {
    return false;
  }

  STopBotInfo *pInfo = getTopBotOutputInfo(pCtx);
  buildTopBotStruct(pInfo, pCtx);

  return true;
}