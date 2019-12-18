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
typedef  int u64_t ;
typedef  int u32_t ;
struct net_buf_simple {int* data; } ;
struct bt_mesh_net_rx {int dummy; } ;

/* Variables and functions */
 int BLE_MESH_NET_IVI_RX (struct bt_mesh_net_rx*) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 

__attribute__((used)) static u64_t msg_hash(struct bt_mesh_net_rx *rx, struct net_buf_simple *pdu)
{
    u32_t hash1, hash2;

    /* Three least significant bytes of IVI + first byte of SEQ */
    hash1 = (BLE_MESH_NET_IVI_RX(rx) << 8) | pdu->data[2];

    /* Two last bytes of SEQ + SRC */
    memcpy(&hash2, &pdu->data[3], 4);

    return (u64_t)hash1 << 32 | (u64_t)hash2;
}