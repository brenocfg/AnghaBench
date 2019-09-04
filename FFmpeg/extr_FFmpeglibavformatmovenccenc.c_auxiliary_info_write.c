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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {scalar_t__ auxiliary_info_size; scalar_t__ auxiliary_info; } ;
typedef  TYPE_1__ MOVMuxCencContext ;

/* Variables and functions */
 int auxiliary_info_alloc_size (TYPE_1__*,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int auxiliary_info_write(MOVMuxCencContext* ctx,
                                         const uint8_t *buf_in, int size)
{
    int ret;

    ret = auxiliary_info_alloc_size(ctx, size);
    if (ret) {
        return ret;
    }
    memcpy(ctx->auxiliary_info + ctx->auxiliary_info_size, buf_in, size);
    ctx->auxiliary_info_size += size;

    return 0;
}