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
typedef  int const u8_t ;
typedef  int /*<<< orphan*/  u32_t ;
struct net_buf_simple {int const* data; int len; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int,...) ; 
 int const NET_MIC_LEN (int const*) ; 
 int /*<<< orphan*/  bt_hex (int const*,int) ; 
 int bt_mesh_ccm_decrypt (int const*,int const*,int const*,int const,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int const*,int const) ; 
 int /*<<< orphan*/  create_net_nonce (int const*,int const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_proxy_nonce (int const*,int const*,int /*<<< orphan*/ ) ; 

int bt_mesh_net_decrypt(const u8_t key[16], struct net_buf_simple *buf,
                        u32_t iv_index, bool proxy)
{
    u8_t mic_len = NET_MIC_LEN(buf->data);
    u8_t nonce[13];

    BT_DBG("PDU (%u bytes) %s", buf->len, bt_hex(buf->data, buf->len));
    BT_DBG("iv_index %u, key %s mic_len %u", iv_index, bt_hex(key, 16),
           mic_len);

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

    buf->len -= mic_len;

    return bt_mesh_ccm_decrypt(key, nonce, &buf->data[7], buf->len - 7,
                               NULL, 0, &buf->data[7], mic_len);
}