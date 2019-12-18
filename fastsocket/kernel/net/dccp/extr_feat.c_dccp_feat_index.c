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

/* Variables and functions */
 int DCCPF_DATA_CHECKSUM ; 
 int DCCPF_RESERVED ; 
#define  DCCPF_SEND_LEV_RATE 128 
 int /*<<< orphan*/  DCCP_FEAT_SUPPORTED_MAX ; 

__attribute__((used)) static int dccp_feat_index(u8 feat_num)
{
	/* The first 9 entries are occupied by the types from RFC 4340, 6.4 */
	if (feat_num > DCCPF_RESERVED && feat_num <= DCCPF_DATA_CHECKSUM)
		return feat_num - 1;

	/*
	 * Other features: add cases for new feature types here after adding
	 * them to the above table.
	 */
	switch (feat_num) {
	case DCCPF_SEND_LEV_RATE:
			return DCCP_FEAT_SUPPORTED_MAX - 1;
	}
	return -1;
}