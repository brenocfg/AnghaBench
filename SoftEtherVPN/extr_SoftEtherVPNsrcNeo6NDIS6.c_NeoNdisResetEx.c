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
typedef  int /*<<< orphan*/  PBOOLEAN ;
typedef  int /*<<< orphan*/  NDIS_STATUS ;
typedef  int /*<<< orphan*/  NDIS_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  NDIS_STATUS_SUCCESS ; 

NDIS_STATUS NeoNdisResetEx(NDIS_HANDLE MiniportAdapterContext, PBOOLEAN AddressingReset)
{
	return NDIS_STATUS_SUCCESS;
}