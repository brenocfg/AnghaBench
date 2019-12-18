#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct in_ifaddr {int /*<<< orphan*/  ifa_address; } ;
struct in_device {scalar_t__ ifa_list; } ;
struct TYPE_5__ {int /*<<< orphan*/  abyIPAddr; TYPE_1__* dev; } ;
struct TYPE_4__ {scalar_t__ ip_ptr; } ;
typedef  TYPE_2__* PSDevice ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) inline static BOOL device_get_ip(PSDevice pInfo) {
    struct in_device* in_dev=(struct in_device*) pInfo->dev->ip_ptr;
    struct in_ifaddr* ifa;

    if (in_dev!=NULL) {
        ifa=(struct in_ifaddr*) in_dev->ifa_list;
        if (ifa!=NULL) {
            memcpy(pInfo->abyIPAddr,&ifa->ifa_address,4);
            return TRUE;
        }
    }
    return FALSE;
}