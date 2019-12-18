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
typedef  int u8 ;
typedef  int u16 ;
struct wb35_mds {int MicAdd; int** MicWriteAddress; size_t MicWriteIndex; int* MicWriteSize; } ;
struct wbsoft_priv {struct wb35_mds Mds; } ;
struct wb35_descriptor {int buffer_total_size; int buffer_start_index; int FragmentThreshold; int** buffer_address; int* buffer_size; int FragmentCount; } ;
struct TYPE_2__ {int T00_frame_length; int T00_first_mpdu; int T00_last_mpdu; int T00_IsLastMpdu; } ;
typedef  TYPE_1__* PT00_DESCRIPTOR ;

/* Variables and functions */
 int DOT_11_SEQUENCE_OFFSET ; 
 int MAX_DESCRIPTOR_BUFFER_INDEX ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 

__attribute__((used)) static u16 Mds_BodyCopy(struct wbsoft_priv *adapter, struct wb35_descriptor *pDes, u8 *TargetBuffer)
{
	PT00_DESCRIPTOR	pT00;
	struct wb35_mds *pMds = &adapter->Mds;
	u8	*buffer;
	u8	*src_buffer;
	u8	*pctmp;
	u16	Size = 0;
	u16	SizeLeft, CopySize, CopyLeft, stmp;
	u8	buf_index, FragmentCount = 0;


	// Copy fragment body
	buffer = TargetBuffer; // shift 8B usb + 24B 802.11
	SizeLeft = pDes->buffer_total_size;
	buf_index = pDes->buffer_start_index;

	pT00 = (PT00_DESCRIPTOR)buffer;
	while (SizeLeft) {
		pT00 = (PT00_DESCRIPTOR)buffer;
		CopySize = SizeLeft;
		if (SizeLeft > pDes->FragmentThreshold) {
			CopySize = pDes->FragmentThreshold;
			pT00->T00_frame_length = 24 + CopySize;//Set USB length
		} else
			pT00->T00_frame_length = 24 + SizeLeft;//Set USB length

		SizeLeft -= CopySize;

		// 1 Byte operation
		pctmp = (u8 *)( buffer + 8 + DOT_11_SEQUENCE_OFFSET );
		*pctmp &= 0xf0;
		*pctmp |= FragmentCount;//931130.5.m
		if( !FragmentCount )
			pT00->T00_first_mpdu = 1;

		buffer += 32; // 8B usb + 24B 802.11 header
		Size += 32;

		// Copy into buffer
		stmp = CopySize + 3;
		stmp &= ~0x03;//4n Alignment
		Size += stmp;// Current 4n offset of mpdu

		while (CopySize) {
			// Copy body
			src_buffer = pDes->buffer_address[buf_index];
			CopyLeft = CopySize;
			if (CopySize >= pDes->buffer_size[buf_index]) {
				CopyLeft = pDes->buffer_size[buf_index];

				// Get the next buffer of descriptor
				buf_index++;
				buf_index %= MAX_DESCRIPTOR_BUFFER_INDEX;
			} else {
				u8	*pctmp = pDes->buffer_address[buf_index];
				pctmp += CopySize;
				pDes->buffer_address[buf_index] = pctmp;
				pDes->buffer_size[buf_index] -= CopySize;
			}

			memcpy(buffer, src_buffer, CopyLeft);
			buffer += CopyLeft;
			CopySize -= CopyLeft;
		}

		// 931130.5.n
		if (pMds->MicAdd) {
			if (!SizeLeft) {
				pMds->MicWriteAddress[ pMds->MicWriteIndex ] = buffer - pMds->MicAdd;
				pMds->MicWriteSize[ pMds->MicWriteIndex ] = pMds->MicAdd;
				pMds->MicAdd = 0;
			}
			else if( SizeLeft < 8 ) //931130.5.p
			{
				pMds->MicAdd = SizeLeft;
				pMds->MicWriteAddress[ pMds->MicWriteIndex ] = buffer - ( 8 - SizeLeft );
				pMds->MicWriteSize[ pMds->MicWriteIndex ] = 8 - SizeLeft;
				pMds->MicWriteIndex++;
			}
		}

		// Does it need to generate the new header for next mpdu?
		if (SizeLeft) {
			buffer = TargetBuffer + Size; // Get the next 4n start address
			memcpy( buffer, TargetBuffer, 32 );//Copy 8B USB +24B 802.11
			pT00 = (PT00_DESCRIPTOR)buffer;
			pT00->T00_first_mpdu = 0;
		}

		FragmentCount++;
	}

	pT00->T00_last_mpdu = 1;
	pT00->T00_IsLastMpdu = 1;
	buffer = (u8 *)pT00 + 8; // +8 for USB hdr
	buffer[1] &= ~0x04; // Clear more frag bit of 802.11 frame control
	pDes->FragmentCount = FragmentCount; // Update the correct fragment number
	return Size;
}