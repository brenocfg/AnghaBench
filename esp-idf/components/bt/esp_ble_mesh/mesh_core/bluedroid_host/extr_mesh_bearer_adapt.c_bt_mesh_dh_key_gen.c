#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8_t ;
typedef  int /*<<< orphan*/  (* bt_mesh_dh_key_cb_t ) (int /*<<< orphan*/  const*,int /*<<< orphan*/  const) ;
struct TYPE_6__ {int /*<<< orphan*/  const* x; int /*<<< orphan*/  const* y; int /*<<< orphan*/  member_0; } ;
struct TYPE_5__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ Point ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  const* BT_OCTET32 ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ) ; 
 size_t BT_OCTET32_LEN ; 
 int /*<<< orphan*/  ECC_PointMult (TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KEY_LENGTH_DWORDS_P256 ; 
 int /*<<< orphan*/  bt_hex (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  const* bt_mesh_private_key ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t) ; 

int bt_mesh_dh_key_gen(const u8_t remote_pk[64], bt_mesh_dh_key_cb_t cb, const u8_t idx)
{
    BT_OCTET32 private_key = {0};
    Point peer_pub_key = {0};
    Point new_pub_key = {0};

    BT_DBG("private key = %s", bt_hex(bt_mesh_private_key, BT_OCTET32_LEN));

    memcpy(private_key, bt_mesh_private_key, BT_OCTET32_LEN);
    memcpy(peer_pub_key.x, remote_pk, BT_OCTET32_LEN);
    memcpy(peer_pub_key.y, &remote_pk[BT_OCTET32_LEN], BT_OCTET32_LEN);

    BT_DBG("remote public key x = %s", bt_hex(peer_pub_key.x, BT_OCTET32_LEN));
    BT_DBG("remote public key y = %s", bt_hex(peer_pub_key.y, BT_OCTET32_LEN));

    ECC_PointMult(&new_pub_key, &peer_pub_key, (DWORD *)private_key, KEY_LENGTH_DWORDS_P256);

    BT_DBG("new public key x = %s", bt_hex(new_pub_key.x, 32));
    BT_DBG("new public key y = %s", bt_hex(new_pub_key.y, 32));

    if (cb != NULL) {
        cb((const u8_t *)new_pub_key.x, idx);
    }

    return 0;
}