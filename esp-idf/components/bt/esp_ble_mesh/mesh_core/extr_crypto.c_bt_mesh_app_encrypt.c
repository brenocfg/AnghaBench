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
typedef  int /*<<< orphan*/  u16_t ;
struct net_buf_simple {int len; int /*<<< orphan*/  const* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  APP_MIC_LEN (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  BT_DBG (char*,int,...) ; 
 int /*<<< orphan*/  bt_hex (int /*<<< orphan*/  const*,int) ; 
 int bt_mesh_ccm_encrypt (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_app_nonce (int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  net_buf_simple_add (struct net_buf_simple*,int /*<<< orphan*/ ) ; 

int bt_mesh_app_encrypt(const u8_t key[16], bool dev_key, u8_t aszmic,
                        struct net_buf_simple *buf, const u8_t *ad,
                        u16_t src, u16_t dst, u32_t seq_num, u32_t iv_index)
{
    u8_t nonce[13];
    int err;

    BT_DBG("AppKey %s", bt_hex(key, 16));
    BT_DBG("dev_key %u src 0x%04x dst 0x%04x", dev_key, src, dst);
    BT_DBG("seq_num 0x%08x iv_index 0x%08x", seq_num, iv_index);
    BT_DBG("Clear: %s", bt_hex(buf->data, buf->len));

    create_app_nonce(nonce, dev_key, aszmic, src, dst, seq_num, iv_index);

    BT_DBG("Nonce  %s", bt_hex(nonce, 13));

    err = bt_mesh_ccm_encrypt(key, nonce, buf->data, buf->len, ad,
                              ad ? 16 : 0, buf->data, APP_MIC_LEN(aszmic));
    if (!err) {
        net_buf_simple_add(buf, APP_MIC_LEN(aszmic));
        BT_DBG("Encr: %s", bt_hex(buf->data, buf->len));
    }

    return err;
}