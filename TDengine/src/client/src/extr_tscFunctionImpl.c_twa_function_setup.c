#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  inputType; } ;
struct TYPE_9__ {TYPE_1__* interResultBuf; } ;
struct TYPE_8__ {int /*<<< orphan*/  type; int /*<<< orphan*/  lastKey; } ;
typedef  TYPE_1__ STwaInfo ;
typedef  TYPE_2__ SResultInfo ;
typedef  TYPE_3__ SQLFunctionCtx ;

/* Variables and functions */
 TYPE_2__* GET_RES_INFO (TYPE_3__*) ; 
 int /*<<< orphan*/  INT64_MIN ; 
 int /*<<< orphan*/  function_setup (TYPE_3__*) ; 

__attribute__((used)) static bool twa_function_setup(SQLFunctionCtx *pCtx) {
  if (!function_setup(pCtx)) {
    return false;
  }

  SResultInfo *pResInfo = GET_RES_INFO(pCtx);  //->aOutputBuf + pCtx->outputBytes;
  STwaInfo *   pInfo = pResInfo->interResultBuf;

  pInfo->lastKey = INT64_MIN;
  pInfo->type = pCtx->inputType;

  return true;
}