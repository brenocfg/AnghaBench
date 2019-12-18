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

/* Variables and functions */
 int bt_mesh_id128 (int /*<<< orphan*/  const*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int bt_mesh_beacon_key(const u8_t net_key[16],
                                     u8_t beacon_key[16])
{
    return bt_mesh_id128(net_key, "nkbk", beacon_key);
}