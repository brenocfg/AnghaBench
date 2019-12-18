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
typedef  int /*<<< orphan*/  u8_t ;
typedef  int /*<<< orphan*/  Point ;

/* Variables and functions */
 int ECC_CheckPointIsInElliCur_P256 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sys_memcpy_swap (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

bool bt_mesh_check_public_key(const u8_t key[64])
{
    struct p256_pub_key {
        u8_t x[32];
        u8_t y[32];
    } check = {0};

    sys_memcpy_swap(check.x, key, 32);
    sys_memcpy_swap(check.y, key + 32, 32);

    return ECC_CheckPointIsInElliCur_P256((Point *)&check);
}