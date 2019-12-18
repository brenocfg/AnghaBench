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
typedef  int /*<<< orphan*/  const u8_t ;
typedef  int /*<<< orphan*/  u32_t ;
struct bt_mesh_subnet_keys {int /*<<< orphan*/  const* net_id; int /*<<< orphan*/  beacon; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_WARN (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bt_hex (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  bt_mesh_beacon_auth (int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static bool auth_match(struct bt_mesh_subnet_keys *keys,
                       const u8_t net_id[8], u8_t flags,
                       u32_t iv_index, const u8_t auth[8])
{
    u8_t net_auth[8];

    if (memcmp(net_id, keys->net_id, 8)) {
        return false;
    }

    bt_mesh_beacon_auth(keys->beacon, flags, keys->net_id, iv_index,
                        net_auth);

    if (memcmp(auth, net_auth, 8)) {
        BT_WARN("Authentication Value %s != %s",
                bt_hex(auth, 8), bt_hex(net_auth, 8));
        return false;
    }

    return true;
}