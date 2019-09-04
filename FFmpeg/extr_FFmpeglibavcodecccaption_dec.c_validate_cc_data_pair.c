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
typedef  int uint8_t ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int AVERROR_PATCHWELCOME ; 
 int /*<<< orphan*/  av_parity (int) ; 

__attribute__((used)) static int validate_cc_data_pair(uint8_t *cc_data_pair)
{
    uint8_t cc_valid = (*cc_data_pair & 4) >>2;
    uint8_t cc_type = *cc_data_pair & 3;

    if (!cc_valid)
        return AVERROR_INVALIDDATA;

    // if EIA-608 data then verify parity.
    if (cc_type==0 || cc_type==1) {
        if (!av_parity(cc_data_pair[2])) {
            return AVERROR_INVALIDDATA;
        }
        if (!av_parity(cc_data_pair[1])) {
            cc_data_pair[1]=0x7F;
        }
    }

    //Skip non-data
    if ((cc_data_pair[0] == 0xFA || cc_data_pair[0] == 0xFC || cc_data_pair[0] == 0xFD)
         && (cc_data_pair[1] & 0x7F) == 0 && (cc_data_pair[2] & 0x7F) == 0)
        return AVERROR_PATCHWELCOME;

    //skip 708 data
    if (cc_type == 3 || cc_type == 2)
        return AVERROR_PATCHWELCOME;

    /* remove parity bit */
    cc_data_pair[1] &= 0x7F;
    cc_data_pair[2] &= 0x7F;

    return 0;
}