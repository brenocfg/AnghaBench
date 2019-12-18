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
 int bt_mesh_aes_cmac_one (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *) ; 

int bt_mesh_prov_conf_salt(const u8_t conf_inputs[145], u8_t salt[16])
{
    const u8_t conf_salt_key[16] = { 0 };

    return bt_mesh_aes_cmac_one(conf_salt_key, conf_inputs, 145, salt);
}