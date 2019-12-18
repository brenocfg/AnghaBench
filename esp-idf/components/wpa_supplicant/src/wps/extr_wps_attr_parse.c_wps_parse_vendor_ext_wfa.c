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
typedef  int u8 ;
typedef  int u16 ;
struct wps_parse_attr {int dummy; } ;

/* Variables and functions */
 scalar_t__ wps_set_vendor_ext_wfa_subelem (struct wps_parse_attr*,int,int,int const*) ; 

__attribute__((used)) static int wps_parse_vendor_ext_wfa(struct wps_parse_attr *attr, const u8 *pos,
				    u16 len)
{
	const u8 *end = pos + len;
	u8 id, elen;

	while (pos + 2 < end) {
		id = *pos++;
		elen = *pos++;
		if (pos + elen > end)
			break;
		if (wps_set_vendor_ext_wfa_subelem(attr, id, elen, pos) < 0)
			return -1;
		pos += elen;
	}

	return 0;
}