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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  u8_t ;
typedef  int /*<<< orphan*/  (* bt_mesh_dh_key_cb_t ) (int /*<<< orphan*/  const*,int /*<<< orphan*/  const) ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BT_OCTET32_LEN ; 
 int /*<<< orphan*/  ble_sm_alg_gen_dhkey (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bt_hex (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bt_mesh_private_key ; 

int bt_mesh_dh_key_gen(const u8_t remote_pk[64], bt_mesh_dh_key_cb_t cb, const u8_t idx)
{
    uint8_t dhkey[32];

    BT_DBG("private key = %s", bt_hex(bt_mesh_private_key, BT_OCTET32_LEN));

    ble_sm_alg_gen_dhkey((uint8_t *)&remote_pk[0], (uint8_t *)&remote_pk[32], bt_mesh_private_key, dhkey);

    if (cb != NULL) {
        cb((const u8_t *)dhkey, idx);
    }
    return 0;
}