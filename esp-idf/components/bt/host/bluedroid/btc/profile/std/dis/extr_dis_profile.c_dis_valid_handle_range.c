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
typedef  scalar_t__ UINT16 ;
struct TYPE_2__ {scalar_t__ service_handle; scalar_t__ max_handle; } ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__ dis_cb ; 

BOOLEAN dis_valid_handle_range(UINT16 handle)
{
    if (handle >= dis_cb.service_handle && handle <= dis_cb.max_handle) {
        return TRUE;
    } else {
        return FALSE;
    }
}