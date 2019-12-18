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
typedef  int tBTA_SERVICE_MASK ;
typedef  int /*<<< orphan*/  UINT8 ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_AG_HFP ; 
 int /*<<< orphan*/  BTA_AG_HSP ; 
 int BTA_HFP_SERVICE_MASK ; 

UINT8 bta_ag_service_to_idx(tBTA_SERVICE_MASK services)
{
    if (services & BTA_HFP_SERVICE_MASK) {
        return BTA_AG_HFP;
    } else {
        return BTA_AG_HSP;
    }
}