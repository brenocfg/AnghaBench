#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t workSpaceSize; int /*<<< orphan*/  cdictLocal; } ;
typedef  TYPE_1__ ZSTD_CCtx ;

/* Variables and functions */
 size_t ZSTD_sizeof_CDict (int /*<<< orphan*/ ) ; 
 size_t ZSTD_sizeof_mtctx (TYPE_1__ const*) ; 

size_t ZSTD_sizeof_CCtx(const ZSTD_CCtx* cctx)
{
    if (cctx==NULL) return 0;   /* support sizeof on NULL */
    return sizeof(*cctx) + cctx->workSpaceSize
           + ZSTD_sizeof_CDict(cctx->cdictLocal)
           + ZSTD_sizeof_mtctx(cctx);
}