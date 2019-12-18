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
typedef  int /*<<< orphan*/  u16_t ;
struct bt_mesh_subnet {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 

int friend_cred_get(struct bt_mesh_subnet *sub, u16_t addr, u8_t *nid,
                    const u8_t **enc, const u8_t **priv)
{
    return -ENOENT;
}