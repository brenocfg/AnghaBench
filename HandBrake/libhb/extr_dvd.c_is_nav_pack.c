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

int is_nav_pack( unsigned char *buf )
{
    /*
     * The NAV Pack is comprised of the PCI Packet and DSI Packet, both
     * of these start at known offsets and start with a special identifier.
     *
     * NAV = {
     *  PCI = { 00 00 01 bf  # private stream header
     *          ?? ??        # length
     *          00           # substream
     *          ...
     *        }
     *  DSI = { 00 00 01 bf  # private stream header
     *          ?? ??        # length
     *          01           # substream
     *          ...
     *        }
     *
     * The PCI starts at offset 0x26 into the sector, and the DSI starts at 0x400
     *
     * This information from: http://dvd.sourceforge.net/dvdinfo/
     */
    if( ( buf[0x26] == 0x00 &&      // PCI
          buf[0x27] == 0x00 &&
          buf[0x28] == 0x01 &&
          buf[0x29] == 0xbf &&
          buf[0x2c] == 0x00 ) &&
        ( buf[0x400] == 0x00 &&     // DSI
          buf[0x401] == 0x00 &&
          buf[0x402] == 0x01 &&
          buf[0x403] == 0xbf &&
          buf[0x406] == 0x01 ) )
    {
        return ( 1 );
    } else {
        return ( 0 );
    }
}