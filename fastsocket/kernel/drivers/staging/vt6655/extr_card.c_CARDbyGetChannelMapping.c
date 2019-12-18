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
typedef  size_t UINT ;
struct TYPE_2__ {scalar_t__ byChannelNumber; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  scalar_t__ CARD_PHY_TYPE ;
typedef  scalar_t__ BYTE ;

/* Variables and functions */
 size_t CB_MAX_CHANNEL ; 
 size_t CB_MAX_CHANNEL_24G ; 
 scalar_t__ PHY_TYPE_11B ; 
 scalar_t__ PHY_TYPE_11G ; 
 TYPE_1__* sChannelTbl ; 

BYTE CARDbyGetChannelMapping (PVOID pDeviceHandler, BYTE byChannelNumber, CARD_PHY_TYPE ePhyType)
{
    UINT        ii;

    if ((ePhyType == PHY_TYPE_11B) || (ePhyType == PHY_TYPE_11G)) {
        return (byChannelNumber);
    }

    for(ii = (CB_MAX_CHANNEL_24G + 1); ii <= CB_MAX_CHANNEL; ) {
        if (sChannelTbl[ii].byChannelNumber == byChannelNumber) {
            return ((BYTE) ii);
        }
        ii++;
    }
    return (0);
}