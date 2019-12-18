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
struct bt_mesh_sg {int member_1; int /*<<< orphan*/  const* member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct bt_mesh_sg*) ; 
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bt_hex (int /*<<< orphan*/  const*,int) ; 
 int bt_mesh_aes_cmac (int /*<<< orphan*/  const*,struct bt_mesh_sg*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int bt_mesh_prov_conf(const u8_t conf_key[16], const u8_t rand[16],
                      const u8_t auth[16], u8_t conf[16])
{
    struct bt_mesh_sg sg[] = { { rand, 16 }, { auth, 16 } };

    BT_DBG("ConfirmationKey %s", bt_hex(conf_key, 16));
    BT_DBG("RandomDevice %s", bt_hex(rand, 16));
    BT_DBG("AuthValue %s", bt_hex(auth, 16));

    return bt_mesh_aes_cmac(conf_key, sg, ARRAY_SIZE(sg), conf);
}