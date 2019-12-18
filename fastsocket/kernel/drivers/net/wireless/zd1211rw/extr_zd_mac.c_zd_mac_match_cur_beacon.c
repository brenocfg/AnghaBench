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
struct TYPE_4__ {TYPE_1__* cur_beacon; } ;
struct zd_mac {TYPE_2__ beacon; } ;
struct sk_buff {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct TYPE_3__ {scalar_t__ len; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static bool zd_mac_match_cur_beacon(struct zd_mac *mac, struct sk_buff *beacon)
{
	if (!mac->beacon.cur_beacon)
		return false;

	if (mac->beacon.cur_beacon->len != beacon->len)
		return false;

	return !memcmp(beacon->data, mac->beacon.cur_beacon->data, beacon->len);
}