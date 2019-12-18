#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  link_key_type; int /*<<< orphan*/  link_key; int /*<<< orphan*/  sec_bd_name; int /*<<< orphan*/  dev_class; int /*<<< orphan*/  bd_addr; } ;
typedef  TYPE_2__ tBTM_SEC_DEV_REC ;
struct TYPE_5__ {int /*<<< orphan*/  (* p_link_key_callback ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_7__ {TYPE_1__ api; } ;

/* Variables and functions */
 TYPE_4__ btm_cb ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void btm_send_link_key_notif (tBTM_SEC_DEV_REC *p_dev_rec)
{
    if (btm_cb.api.p_link_key_callback) {
        (*btm_cb.api.p_link_key_callback) (p_dev_rec->bd_addr, p_dev_rec->dev_class,
                                           p_dev_rec->sec_bd_name, p_dev_rec->link_key,
                                           p_dev_rec->link_key_type);
    }
}