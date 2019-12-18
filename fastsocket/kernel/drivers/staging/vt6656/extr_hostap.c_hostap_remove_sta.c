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
struct viawget_hostapd_param {int /*<<< orphan*/  sta_addr; } ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  PSDevice ;

/* Variables and functions */
 scalar_t__ BSSbIsSTAInNodeDB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BSSvRemoveOneNode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ENOENT ; 

__attribute__((used)) static int hostap_remove_sta(PSDevice pDevice,
				     struct viawget_hostapd_param *param)
{
	UINT uNodeIndex;


    if (BSSbIsSTAInNodeDB(pDevice, param->sta_addr, &uNodeIndex)) {
        BSSvRemoveOneNode(pDevice, uNodeIndex);
    }
    else {
        return -ENOENT;
    }
	return 0;
}