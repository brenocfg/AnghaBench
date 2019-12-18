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
struct net_buf {int dummy; } ;
typedef  int /*<<< orphan*/  s32_t ;
typedef  enum bt_mesh_adv_type { ____Placeholder_bt_mesh_adv_type } bt_mesh_adv_type ;

/* Variables and functions */
 int /*<<< orphan*/  adv_alloc ; 
 int /*<<< orphan*/  adv_buf_pool ; 
 struct net_buf* bt_mesh_adv_create_from_pool (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct net_buf *bt_mesh_adv_create(enum bt_mesh_adv_type type, u8_t xmit,
                                   s32_t timeout)
{
    return bt_mesh_adv_create_from_pool(&adv_buf_pool, adv_alloc, type,
                                        xmit, timeout);
}