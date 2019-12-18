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
typedef  int /*<<< orphan*/  UINT8 ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_SP_KEY_NOTIF_EVT ; 
 int /*<<< orphan*/  btm_proc_sp_req_evt (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void btu_hcif_user_passkey_notif_evt (UINT8 *p)
{
    btm_proc_sp_req_evt(BTM_SP_KEY_NOTIF_EVT, p);
}