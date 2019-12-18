#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t u32 ;
typedef  int u16 ;
struct wb35_rx {size_t RxProcessIndex; int* RxOwner; int* RxBufferSize; int /*<<< orphan*/  Ep3ErrorCount2; int /*<<< orphan*/  EP3vm_state; int /*<<< orphan*/ * pDRx; } ;
struct hw_data {struct wb35_rx Wb35Rx; } ;
struct wbsoft_priv {struct hw_data sHwData; } ;
struct TYPE_4__ {void* value; } ;
struct TYPE_3__ {scalar_t__ R00_receive_byte_count; void* value; } ;
struct wb35_descriptor {int* buffer_size; int buffer_number; int buffer_total_size; scalar_t__ buffer_start_index; int /*<<< orphan*/ ** buffer_address; TYPE_2__ R01; TYPE_1__ R00; } ;
struct ieee80211_hw {struct wbsoft_priv* priv; } ;

/* Variables and functions */
 int MAX_PACKET_SIZE ; 
 size_t MAX_USB_RX_BUFFER_NUMBER ; 
 int RX_END_TAG ; 
 int /*<<< orphan*/  VM_STOP ; 
 int /*<<< orphan*/  Wb35Rx_adjust (struct wb35_descriptor*) ; 
 int cpu_to_le32 (size_t) ; 
 void* le32_to_cpu (size_t) ; 
 int /*<<< orphan*/  packet_came (struct ieee80211_hw*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  printk (char*,int) ; 

__attribute__((used)) static u16 Wb35Rx_indicate(struct ieee80211_hw *hw)
{
	struct wbsoft_priv *priv = hw->priv;
	struct hw_data * pHwData = &priv->sHwData;
	struct wb35_descriptor	RxDes;
	struct wb35_rx *pWb35Rx = &pHwData->Wb35Rx;
	u8 *		pRxBufferAddress;
	u16		PacketSize;
	u16		stmp, BufferSize, stmp2 = 0;
	u32		RxBufferId;

	// Only one thread be allowed to run into the following
	do {
		RxBufferId = pWb35Rx->RxProcessIndex;
		if (pWb35Rx->RxOwner[ RxBufferId ]) //Owner by VM
			break;

		pWb35Rx->RxProcessIndex++;
		pWb35Rx->RxProcessIndex %= MAX_USB_RX_BUFFER_NUMBER;

		pRxBufferAddress = pWb35Rx->pDRx;
		BufferSize = pWb35Rx->RxBufferSize[ RxBufferId ];

		// Parse the bulkin buffer
		while (BufferSize >= 4) {
			if ((cpu_to_le32(*(u32 *)pRxBufferAddress) & 0x0fffffff) == RX_END_TAG) //Is ending? 921002.9.a
				break;

			// Get the R00 R01 first
			RxDes.R00.value = le32_to_cpu(*(u32 *)pRxBufferAddress);
			PacketSize = (u16)RxDes.R00.R00_receive_byte_count;
			RxDes.R01.value = le32_to_cpu(*((u32 *)(pRxBufferAddress+4)));
			// For new DMA 4k
			if ((PacketSize & 0x03) > 0)
				PacketSize -= 4;

			// Basic check for Rx length. Is length valid?
			if (PacketSize > MAX_PACKET_SIZE) {
				#ifdef _PE_RX_DUMP_
				printk("Serious ERROR : Rx data size too long, size =%d\n", PacketSize);
				#endif

				pWb35Rx->EP3vm_state = VM_STOP;
				pWb35Rx->Ep3ErrorCount2++;
				break;
			}

			// Start to process Rx buffer
//			RxDes.Descriptor_ID = RxBufferId; // Due to synchronous indicate, the field doesn't necessary to use.
			BufferSize -= 8; //subtract 8 byte for 35's USB header length
			pRxBufferAddress += 8;

			RxDes.buffer_address[0] = pRxBufferAddress;
			RxDes.buffer_size[0] = PacketSize;
			RxDes.buffer_number = 1;
			RxDes.buffer_start_index = 0;
			RxDes.buffer_total_size = RxDes.buffer_size[0];
			Wb35Rx_adjust(&RxDes);

			packet_came(hw, pRxBufferAddress, PacketSize);

			// Move RxBuffer point to the next
			stmp = PacketSize + 3;
			stmp &= ~0x03; // 4n alignment
			pRxBufferAddress += stmp;
			BufferSize -= stmp;
			stmp2 += stmp;
		}

		// Reclaim resource
		pWb35Rx->RxOwner[ RxBufferId ] = 1;
	} while (true);

	return stmp2;
}