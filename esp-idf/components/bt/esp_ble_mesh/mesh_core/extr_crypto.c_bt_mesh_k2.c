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
typedef  int u8_t ;
struct bt_mesh_sg {int const* data; size_t len; } ;
typedef  int /*<<< orphan*/  pad ;
typedef  int /*<<< orphan*/  out ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct bt_mesh_sg*) ; 
 int /*<<< orphan*/  BT_DBG (char*,int,...) ; 
 int /*<<< orphan*/  bt_hex (int const*,int) ; 
 int bt_mesh_aes_cmac (int*,struct bt_mesh_sg*,int /*<<< orphan*/ ,int*) ; 
 int bt_mesh_aes_cmac_one (int*,int const*,int,int*) ; 
 int bt_mesh_s1 (char*,int*) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 

int bt_mesh_k2(const u8_t n[16], const u8_t *p, size_t p_len,
               u8_t net_id[1], u8_t enc_key[16], u8_t priv_key[16])
{
    struct bt_mesh_sg sg[3];
    u8_t salt[16];
    u8_t out[16];
    u8_t t[16];
    u8_t pad;
    int err;

    BT_DBG("n %s", bt_hex(n, 16));
    BT_DBG("p %s", bt_hex(p, p_len));

    err = bt_mesh_s1("smk2", salt);
    if (err) {
        return err;
    }

    err = bt_mesh_aes_cmac_one(salt, n, 16, t);
    if (err) {
        return err;
    }

    pad = 0x01;

    sg[0].data = NULL;
    sg[0].len  = 0;
    sg[1].data = p;
    sg[1].len  = p_len;
    sg[2].data = &pad;
    sg[2].len  = sizeof(pad);

    err = bt_mesh_aes_cmac(t, sg, ARRAY_SIZE(sg), out);
    if (err) {
        return err;
    }

    net_id[0] = out[15] & 0x7f;

    sg[0].data = out;
    sg[0].len  = sizeof(out);
    pad = 0x02;

    err = bt_mesh_aes_cmac(t, sg, ARRAY_SIZE(sg), out);
    if (err) {
        return err;
    }

    memcpy(enc_key, out, 16);

    pad = 0x03;

    err = bt_mesh_aes_cmac(t, sg, ARRAY_SIZE(sg), out);
    if (err) {
        return err;
    }

    memcpy(priv_key, out, 16);

    BT_DBG("NID 0x%02x enc_key %s", net_id[0], bt_hex(enc_key, 16));
    BT_DBG("priv_key %s", bt_hex(priv_key, 16));

    return 0;
}