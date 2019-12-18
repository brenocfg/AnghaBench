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
typedef  int /*<<< orphan*/  u32_t ;

/* Variables and functions */
 int /*<<< orphan*/  sys_put_be32 (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void create_net_nonce(u8_t nonce[13], const u8_t *pdu,
                             u32_t iv_index)
{
    /* Nonce Type */
    nonce[0] = 0x00;

    /* FRND + TTL */
    nonce[1] = pdu[1];

    /* Sequence Number */
    nonce[2] = pdu[2];
    nonce[3] = pdu[3];
    nonce[4] = pdu[4];

    /* Source Address */
    nonce[5] = pdu[5];
    nonce[6] = pdu[6];

    /* Pad */
    nonce[7] = 0U;
    nonce[8] = 0U;

    /* IV Index */
    sys_put_be32(iv_index, &nonce[9]);
}