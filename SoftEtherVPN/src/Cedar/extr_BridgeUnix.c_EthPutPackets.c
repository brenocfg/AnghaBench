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
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  ETH ;

/* Variables and functions */
 int /*<<< orphan*/  EthPutPacket (int /*<<< orphan*/ *,void*,scalar_t__) ; 

void EthPutPackets(ETH *e, UINT num, void **datas, UINT *sizes)
{
	UINT i;
	// Validate arguments
	if (e == NULL || num == 0 || datas == NULL || sizes == NULL)
	{
		return;
	}

	for (i = 0;i < num;i++)
	{
		EthPutPacket(e, datas[i], sizes[i]);
	}
}