#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  inputType; int /*<<< orphan*/  inputBytes; int /*<<< orphan*/  aOutputBuf; int /*<<< orphan*/  size; } ;
typedef  TYPE_1__ SQLFunctionCtx ;

/* Variables and functions */
 char* GET_INPUT_CHAR (TYPE_1__*) ; 
 int /*<<< orphan*/  SET_VAL (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  assignVal (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void copy_function(SQLFunctionCtx *pCtx) {
  SET_VAL(pCtx, pCtx->size, 1);

  char *pData = GET_INPUT_CHAR(pCtx);
  assignVal(pCtx->aOutputBuf, pData, pCtx->inputBytes, pCtx->inputType);
}