#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT8 ;
struct TYPE_2__ {int /*<<< orphan*/  max_collision_delay; int /*<<< orphan*/  pairing_bda; int /*<<< orphan*/  security_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  BD_ADDR_LEN ; 
 int /*<<< orphan*/  BTM_SEC_MAX_COLLISION_DELAY ; 
 TYPE_1__ btm_cb ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void btm_sec_init (UINT8 sec_mode)
{
    btm_cb.security_mode = sec_mode;
    memset (btm_cb.pairing_bda, 0xff, BD_ADDR_LEN);
    btm_cb.max_collision_delay = BTM_SEC_MAX_COLLISION_DELAY;
}