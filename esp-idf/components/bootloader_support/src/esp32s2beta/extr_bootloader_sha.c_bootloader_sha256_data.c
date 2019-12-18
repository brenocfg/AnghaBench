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
typedef  int /*<<< orphan*/ * bootloader_sha256_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ctx ; 
 int /*<<< orphan*/  ets_sha_update (int /*<<< orphan*/ *,void const*,size_t,int) ; 

void bootloader_sha256_data(bootloader_sha256_handle_t handle, const void *data, size_t data_len)
{
    assert(handle != NULL);
    assert(data_len % 4 == 0);
    ets_sha_update(&ctx, data, data_len, false);
}