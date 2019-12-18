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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int ETH_ALEN ; 
 int memcmp (void const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  os_bzero (int /*<<< orphan*/ *,int) ; 

int hostapd_mac_comp_empty(const void *a)
{
    u8 empty[ETH_ALEN];

    os_bzero(empty, ETH_ALEN);

    return memcmp(a, empty, ETH_ALEN);
}