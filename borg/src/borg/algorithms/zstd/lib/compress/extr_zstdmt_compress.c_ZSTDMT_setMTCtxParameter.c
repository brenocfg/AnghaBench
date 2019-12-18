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
typedef  int /*<<< orphan*/  ZSTDMT_parameter ;
struct TYPE_3__ {int /*<<< orphan*/  params; } ;
typedef  TYPE_1__ ZSTDMT_CCtx ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGLOG (int,char*) ; 
 size_t ZSTDMT_CCtxParam_setMTCtxParameter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

size_t ZSTDMT_setMTCtxParameter(ZSTDMT_CCtx* mtctx, ZSTDMT_parameter parameter, int value)
{
    DEBUGLOG(4, "ZSTDMT_setMTCtxParameter");
    return ZSTDMT_CCtxParam_setMTCtxParameter(&mtctx->params, parameter, value);
}