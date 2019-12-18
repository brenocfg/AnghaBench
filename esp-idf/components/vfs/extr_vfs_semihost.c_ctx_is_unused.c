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
struct TYPE_3__ {scalar_t__* base_path; } ;
typedef  TYPE_1__ vfs_semihost_ctx_t ;

/* Variables and functions */

inline bool ctx_is_unused(const vfs_semihost_ctx_t* ctx)
{
    return ctx->base_path[0] == 0;
}