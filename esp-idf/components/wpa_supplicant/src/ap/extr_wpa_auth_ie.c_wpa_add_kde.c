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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 scalar_t__ RSN_SELECTOR_LEN ; 
 int /*<<< orphan*/  RSN_SELECTOR_PUT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WLAN_EID_VENDOR_SPECIFIC ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 

u8 * wpa_add_kde(u8 *pos, u32 kde, const u8 *data, size_t data_len,
		 const u8 *data2, size_t data2_len)
{
	*pos++ = WLAN_EID_VENDOR_SPECIFIC;
	*pos++ = RSN_SELECTOR_LEN + data_len + data2_len;
	RSN_SELECTOR_PUT(pos, kde);
	pos += RSN_SELECTOR_LEN;
	memcpy(pos, data, data_len);
	pos += data_len;
	if (data2) {
		memcpy(pos, data2, data2_len);
		pos += data2_len;
	}
	return pos;
}