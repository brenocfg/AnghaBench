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
typedef  int /*<<< orphan*/  sign_data ;
typedef  scalar_t__ UINT ;
typedef  int UCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int*,int*,int) ; 
 int /*<<< orphan*/  HASHED_DATA (int*) ; 
 scalar_t__ MIN_SIGN_HASH_SIZE ; 
 int /*<<< orphan*/  Sha1 (int /*<<< orphan*/ ,void*,scalar_t__) ; 

bool HashForSign(void *dst, UINT dst_size, void *src, UINT src_size)
{
	UCHAR *buf = (UCHAR *)dst;
	UCHAR sign_data[] =
	{
		0x30, 0x21, 0x30, 0x09, 0x06, 0x05, 0x2B, 0x0E,
		0x03, 0x02, 0x1A, 0x05, 0x00, 0x04, 0x14,
	};
	// Validate arguments
	if (dst == NULL || src == NULL || src_size == 0 || MIN_SIGN_HASH_SIZE > dst_size)
	{
		return false;
	}

	// Header part
	Copy(buf, sign_data, sizeof(sign_data));

	// Hash
	Sha1(HASHED_DATA(buf), src, src_size);

	return true;
}