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
struct mac_acl_entry {int vlan_id; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

int hostapd_maclist_found(struct mac_acl_entry *list, int num_entries,
              const u8 *addr, int *vlan_id)
{
    int start, end, middle, res;

    start = 0;
    end = num_entries - 1;

    while (start <= end) {
        middle = (start + end) / 2;
        res = memcmp(list[middle].addr, addr, ETH_ALEN);
        if (res == 0) {
            if (vlan_id)
                *vlan_id = list[middle].vlan_id;
            return 1;
        }
        if (res < 0)
            start = middle + 1;
        else
            end = middle - 1;
    }

    return 0;
}