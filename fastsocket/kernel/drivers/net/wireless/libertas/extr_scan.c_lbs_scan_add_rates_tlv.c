#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_2__ {void* len; void* type; } ;
struct mrvl_ie_rates_param_set {TYPE_1__ header; } ;

/* Variables and functions */
 int MAX_RATES ; 
 int TLV_TYPE_RATES ; 
 void* cpu_to_le16 (int) ; 
 int* lbs_bg_rates ; 

__attribute__((used)) static int lbs_scan_add_rates_tlv(uint8_t *tlv)
{
	int i;
	struct mrvl_ie_rates_param_set *rate_tlv = (void *)tlv;

	rate_tlv->header.type = cpu_to_le16(TLV_TYPE_RATES);
	tlv += sizeof(rate_tlv->header);
	for (i = 0; i < MAX_RATES; i++) {
		*tlv = lbs_bg_rates[i];
		if (*tlv == 0)
			break;
		/* This code makes sure that the 802.11b rates (1 MBit/s, 2
		   MBit/s, 5.5 MBit/s and 11 MBit/s get's the high bit set.
		   Note that the values are MBit/s * 2, to mark them as
		   basic rates so that the firmware likes it better */
		if (*tlv == 0x02 || *tlv == 0x04 ||
		    *tlv == 0x0b || *tlv == 0x16)
			*tlv |= 0x80;
		tlv++;
	}
	rate_tlv->header.len = cpu_to_le16(i);
	return sizeof(rate_tlv->header) + i;
}