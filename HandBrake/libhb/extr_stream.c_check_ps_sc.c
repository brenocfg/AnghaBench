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

__attribute__((used)) static int check_ps_sc(const uint8_t *buf)
{
    // a legal MPEG program stream must start with a Pack followed by a
    // some other start code. If we've already verified the pack, this skip
    // it and checks for a start code prefix.
    int pos;
    int mark = buf[4] >> 4;
    if ( mark == 0x02 )
    {
        // Check other marker bits to make it less likely
        // that we are being spoofed.
        if( ( buf[4] & 0xf1 ) != 0x21 ||
            ( buf[6] & 0x01 ) != 0x01 ||
            ( buf[8] & 0x01 ) != 0x01 ||
            ( buf[9] & 0x80 ) != 0x80 ||
            ( buf[11] & 0x01 ) != 0x01 )
        {
            return 0;
        }
        // mpeg-1 pack header
        pos = 12;   // skip over the PACK
    }
    else
    {
        // Check other marker bits to make it less likely
        // that we are being spoofed.
        if( ( buf[4] & 0xC4 ) != 0x44 ||
            ( buf[6] & 0x04 ) != 0x04 ||
            ( buf[8] & 0x04 ) != 0x04 ||
            ( buf[9] & 0x01 ) != 0x01 ||
            ( buf[12] & 0x03 ) != 0x03 )
        {
            return 0;
        }
        // mpeg-2 pack header
        pos = 14 + ( buf[13] & 0x7 );   // skip over the PACK
    }
    return (buf[pos+0] == 0x00) && (buf[pos+1] == 0x00) && (buf[pos+2] == 0x01);
}