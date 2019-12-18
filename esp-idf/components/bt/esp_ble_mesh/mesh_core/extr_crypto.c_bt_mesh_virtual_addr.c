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
typedef  int u16_t ;

/* Variables and functions */
 int bt_mesh_aes_cmac_one (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *) ; 
 int bt_mesh_s1 (char*,int /*<<< orphan*/ *) ; 
 int sys_get_be16 (int /*<<< orphan*/ *) ; 

int bt_mesh_virtual_addr(const u8_t virtual_label[16], u16_t *addr)
{
    u8_t salt[16];
    u8_t tmp[16];
    int err;

    err = bt_mesh_s1("vtad", salt);
    if (err) {
        return err;
    }

    err = bt_mesh_aes_cmac_one(salt, virtual_label, 16, tmp);
    if (err) {
        return err;
    }

    *addr = (sys_get_be16(&tmp[14]) & 0x3fff) | 0x8000;

    return 0;
}