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
typedef  int /*<<< orphan*/  u8 ;
struct wb35_tx {int /*<<< orphan*/ ** TxBuffer; } ;
struct hw_data {struct wb35_tx Wb35Tx; } ;

/* Variables and functions */

unsigned char
Wb35Tx_get_tx_buffer(struct hw_data * pHwData, u8 **pBuffer)
{
	struct wb35_tx *pWb35Tx = &pHwData->Wb35Tx;

	*pBuffer = pWb35Tx->TxBuffer[0];
	return true;
}