#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  nType; } ;
struct TYPE_5__ {TYPE_3__ tag; int /*<<< orphan*/  aOutputBuf; } ;
typedef  TYPE_1__ SQLFunctionCtx ;

/* Variables and functions */
 int /*<<< orphan*/  SET_VAL (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  tVariantDump (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tag_function(SQLFunctionCtx *pCtx) {
  SET_VAL(pCtx, 1, 1);
  tVariantDump(&pCtx->tag, pCtx->aOutputBuf, pCtx->tag.nType);
}