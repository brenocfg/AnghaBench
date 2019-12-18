#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  customFree; int /*<<< orphan*/  customAlloc; } ;
typedef  TYPE_2__ ZSTD_customMem ;
struct TYPE_7__ {int contentSizeFlag; } ;
struct TYPE_9__ {TYPE_1__ fParams; int /*<<< orphan*/  compressionLevel; TYPE_2__ customMem; } ;
typedef  TYPE_3__ ZSTD_CCtx_params ;

/* Variables and functions */
 int /*<<< orphan*/  ZSTD_CLEVEL_DEFAULT ; 
 scalar_t__ ZSTD_calloc (int,TYPE_2__) ; 

__attribute__((used)) static ZSTD_CCtx_params* ZSTD_createCCtxParams_advanced(
        ZSTD_customMem customMem)
{
    ZSTD_CCtx_params* params;
    if (!customMem.customAlloc ^ !customMem.customFree) return NULL;
    params = (ZSTD_CCtx_params*)ZSTD_calloc(
            sizeof(ZSTD_CCtx_params), customMem);
    if (!params) { return NULL; }
    params->customMem = customMem;
    params->compressionLevel = ZSTD_CLEVEL_DEFAULT;
    params->fParams.contentSizeFlag = 1;
    return params;
}