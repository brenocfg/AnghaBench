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
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  os_memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 

size_t wpa_merge_byte_arrays(u8 *res, size_t res_len,
			 const u8 *src1, size_t src1_len,
			 const u8 *src2, size_t src2_len)
{
	size_t len = 0;

	os_memset(res, 0, res_len);

	if (src1) {
		if (src1_len >= res_len) {
			os_memcpy(res, src1, res_len);
			return res_len;
		}

		os_memcpy(res, src1, src1_len);
		len += src1_len;
	}

	if (src2) {
		if (len + src2_len >= res_len) {
			os_memcpy(res + len, src2, res_len - len);
			return res_len;
		}

		os_memcpy(res + len, src2, src2_len);
		len += src2_len;
	}

	return len;
}