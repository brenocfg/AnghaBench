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
struct bt_mesh_sg {void const* member_0; size_t member_1; } ;

/* Variables and functions */
 int bt_mesh_aes_cmac (int /*<<< orphan*/  const*,struct bt_mesh_sg*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int bt_mesh_aes_cmac_one(const u8_t key[16], const void *m,
                                       size_t len, u8_t mac[16])
{
    struct bt_mesh_sg sg = { m, len };

    return bt_mesh_aes_cmac(key, &sg, 1, mac);
}