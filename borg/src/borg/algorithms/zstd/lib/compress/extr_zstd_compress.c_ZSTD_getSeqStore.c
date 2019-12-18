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
typedef  int /*<<< orphan*/  seqStore_t ;
struct TYPE_3__ {int /*<<< orphan*/  const seqStore; } ;
typedef  TYPE_1__ ZSTD_CCtx ;

/* Variables and functions */

const seqStore_t* ZSTD_getSeqStore(const ZSTD_CCtx* ctx) { return &(ctx->seqStore); }