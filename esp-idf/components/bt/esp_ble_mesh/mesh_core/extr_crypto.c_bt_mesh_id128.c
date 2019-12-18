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

/* Variables and functions */
 int bt_mesh_k1 (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int bt_mesh_s1 (char const*,int /*<<< orphan*/ *) ; 

int bt_mesh_id128(const u8_t n[16], const char *s, u8_t out[16])
{
    const char *id128 = "id128\x01";
    u8_t salt[16];
    int err;

    err = bt_mesh_s1(s, salt);
    if (err) {
        return err;
    }

    return bt_mesh_k1(n, 16, salt, id128, out);
}