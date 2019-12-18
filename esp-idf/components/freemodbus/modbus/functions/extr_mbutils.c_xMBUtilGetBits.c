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
typedef  int USHORT ;
typedef  int UCHAR ;

/* Variables and functions */
 int BITS_UCHAR ; 

UCHAR
xMBUtilGetBits( UCHAR * ucByteBuf, USHORT usBitOffset, UCHAR ucNBits )
{
    USHORT          usWordBuf;
    USHORT          usMask;
    USHORT          usByteOffset;
    USHORT          usNPreBits;

    /* Calculate byte offset for first byte containing the bit values starting
     * at usBitOffset. */
    usByteOffset = ( USHORT )( ( usBitOffset ) / BITS_UCHAR );

    /* How many bits precede our bits to set. */
    usNPreBits = ( USHORT )( usBitOffset - usByteOffset * BITS_UCHAR );

    /* Prepare a mask for setting the new bits. */
    usMask = ( USHORT )( ( 1 << ( USHORT ) ucNBits ) - 1 );

    /* copy bits into temporary storage. */
    usWordBuf = ucByteBuf[usByteOffset];
    usWordBuf |= ucByteBuf[usByteOffset + 1] << BITS_UCHAR;

    /* throw away unneeded bits. */
    usWordBuf >>= usNPreBits;

    /* mask away bits above the requested bitfield. */
    usWordBuf &= usMask;

    return ( UCHAR ) usWordBuf;
}