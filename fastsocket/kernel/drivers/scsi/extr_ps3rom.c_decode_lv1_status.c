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
typedef  int u64 ;

/* Variables and functions */
 int SAM_STAT_CHECK_CONDITION ; 

__attribute__((used)) static int decode_lv1_status(u64 status, unsigned char *sense_key,
			     unsigned char *asc, unsigned char *ascq)
{
	if (((status >> 24) & 0xff) != SAM_STAT_CHECK_CONDITION)
		return -1;

	*sense_key = (status >> 16) & 0xff;
	*asc       = (status >>  8) & 0xff;
	*ascq      =  status        & 0xff;
	return 0;
}