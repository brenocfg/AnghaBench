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
typedef  unsigned int u8_t ;
struct seg_rx {scalar_t__ ttl; unsigned int seg_n; int /*<<< orphan*/  block; } ;
typedef  int /*<<< orphan*/  s32_t ;

/* Variables and functions */
 scalar_t__ BLE_MESH_TTL_DEFAULT ; 
 int /*<<< orphan*/  K_MSEC (int) ; 
 int /*<<< orphan*/  MAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int bt_mesh_default_ttl_get () ; 
 unsigned int popcount (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline s32_t ack_timeout(struct seg_rx *rx)
{
    s32_t to;
    u8_t ttl;

    if (rx->ttl == BLE_MESH_TTL_DEFAULT) {
        ttl = bt_mesh_default_ttl_get();
    } else {
        ttl = rx->ttl;
    }

    /* The acknowledgment timer shall be set to a minimum of
     * 150 + 50 * TTL milliseconds.
     */
    to = K_MSEC(150 + (ttl * 50U));

    /* 100 ms for every not yet received segment */
    to += K_MSEC(((rx->seg_n + 1) - popcount(rx->block)) * 100U);

    /* Make sure we don't send more frequently than the duration for
     * each packet (default is 300ms).
     */
    return MAX(to, K_MSEC(400));
}