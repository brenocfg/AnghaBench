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
typedef  int /*<<< orphan*/  AVHWDeviceContext ;

/* Variables and functions */
 int /*<<< orphan*/  MFX_IMPL_HARDWARE_ANY ; 
 int qsv_device_derive_from_child (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int qsv_device_derive(AVHWDeviceContext *ctx,
                             AVHWDeviceContext *child_device_ctx, int flags)
{
    return qsv_device_derive_from_child(ctx, MFX_IMPL_HARDWARE_ANY,
                                        child_device_ctx, flags);
}