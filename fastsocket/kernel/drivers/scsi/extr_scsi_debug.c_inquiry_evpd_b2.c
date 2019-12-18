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

/* Variables and functions */
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ scsi_debug_lbpu ; 
 scalar_t__ scsi_debug_lbpws ; 
 scalar_t__ scsi_debug_lbpws10 ; 

__attribute__((used)) static int inquiry_evpd_b2(unsigned char *arr)
{
	memset(arr, 0, 0x8);
	arr[0] = 0;			/* threshold exponent */

	if (scsi_debug_lbpu)
		arr[1] = 1 << 7;

	if (scsi_debug_lbpws)
		arr[1] |= 1 << 6;

	if (scsi_debug_lbpws10)
		arr[1] |= 1 << 5;

	return 0x8;
}