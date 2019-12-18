#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint16_t ;
typedef  size_t UINT16 ;
struct TYPE_4__ {TYPE_1__* acl_db; } ;
struct TYPE_3__ {scalar_t__ in_use; } ;

/* Variables and functions */
 size_t MAX_L2CAP_LINKS ; 
 TYPE_2__ btm_cb ; 

UINT16 BTM_GetNumAclLinks (void)
{
    uint16_t num_acl = 0;

    for (uint16_t i = 0; i < MAX_L2CAP_LINKS; ++i) {
        if (btm_cb.acl_db[i].in_use) {
            ++num_acl;
        }
    }

    return num_acl;
}