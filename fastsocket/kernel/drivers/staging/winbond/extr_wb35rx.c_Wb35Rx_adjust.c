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
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_2__ {int R01_decryption_method; } ;
struct wb35_descriptor {int** buffer_address; int* buffer_size; TYPE_1__ R01; } ;

/* Variables and functions */

__attribute__((used)) static void Wb35Rx_adjust(struct wb35_descriptor *pRxDes)
{
	u32 *	pRxBufferAddress;
	u32	DecryptionMethod;
	u32	i;
	u16	BufferSize;

	DecryptionMethod = pRxDes->R01.R01_decryption_method;
	pRxBufferAddress = pRxDes->buffer_address[0];
	BufferSize = pRxDes->buffer_size[0];

	// Adjust the last part of data. Only data left
	BufferSize -= 4; // For CRC-32
	if (DecryptionMethod)
		BufferSize -= 4;
	if (DecryptionMethod == 3) // For CCMP
		BufferSize -= 4;

	// Adjust the IV field which after 802.11 header and ICV field.
	if (DecryptionMethod == 1) // For WEP
	{
		for( i=6; i>0; i-- )
			pRxBufferAddress[i] = pRxBufferAddress[i-1];
		pRxDes->buffer_address[0] = pRxBufferAddress + 1;
		BufferSize -= 4; // 4 byte for IV
	}
	else if( DecryptionMethod ) // For TKIP and CCMP
	{
		for (i=7; i>1; i--)
			pRxBufferAddress[i] = pRxBufferAddress[i-2];
		pRxDes->buffer_address[0] = pRxBufferAddress + 2;//Update the descriptor, shift 8 byte
		BufferSize -= 8; // 8 byte for IV + ICV
	}
	pRxDes->buffer_size[0] = BufferSize;
}