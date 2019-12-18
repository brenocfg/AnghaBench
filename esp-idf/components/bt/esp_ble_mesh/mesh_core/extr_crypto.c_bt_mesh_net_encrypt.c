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
struct net_buf_simple {int len; int /*<<< orphan*/  const* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int,...) ; 
 int /*<<< orphan*/  const NET_MIC_LEN (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  bt_hex (int /*<<< orphan*/  const*,int) ; 
 int bt_mesh_ccm_encrypt (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  create_net_nonce (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_proxy_nonce (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  net_buf_simple_add (struct net_buf_simple*,int /*<<< orphan*/  const) ; 

int bt_mesh_net_encrypt(const u8_t key[16], struct net_buf_simple *buf,
                        u32_t iv_index, bool proxy)
{
    u8_t mic_len = NET_MIC_LEN(buf->data);
    u8_t nonce[13];
    int err;

    BT_DBG("IVIndex %u EncKey %s mic_len %u", iv_index, bt_hex(key, 16),
           mic_len);
    BT_DBG("PDU (len %u) %s", buf->len, bt_hex(buf->data, buf->len));

#if defined(CONFIG_BLE_MESH_PROXY)
    if (proxy) {
        create_proxy_nonce(nonce, buf->data, iv_index);
    } else {
        create_net_nonce(nonce, buf->data, iv_index);
    }
#else
    create_net_nonce(nonce, buf->data, iv_index);
#endif

    BT_DBG("Nonce %s", bt_hex(nonce, 13));

    err = bt_mesh_ccm_encrypt(key, nonce, &buf->data[7], buf->len - 7,
                              NULL, 0, &buf->data[7], mic_len);
    if (!err) {
        net_buf_simple_add(buf, mic_len);
    }

    return err;
}