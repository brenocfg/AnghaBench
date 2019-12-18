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
typedef  int /*<<< orphan*/  DWORD_PTR ;
typedef  scalar_t__ BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ CB_MAX_CHANNEL_24G ; 
 int /*<<< orphan*/  IFRFbWriteEmbeded (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * dwAL7230InitTable ; 
 int /*<<< orphan*/ * dwAL7230InitTableAMode ; 

BOOL RFbAL7230SelectChannelPostProcess (DWORD_PTR dwIoBase, BYTE byOldChannel, BYTE byNewChannel)
{
    BOOL    bResult;

    bResult = TRUE;

    // if change between 11 b/g and 11a need to update the following register
    // Channel Index 1~14

    if( (byOldChannel <= CB_MAX_CHANNEL_24G) && (byNewChannel > CB_MAX_CHANNEL_24G) )
    {
        // Change from 2.4G to 5G
        bResult &= IFRFbWriteEmbeded(dwIoBase, dwAL7230InitTableAMode[2]); //Reg2
        bResult &= IFRFbWriteEmbeded(dwIoBase, dwAL7230InitTableAMode[3]); //Reg3
        bResult &= IFRFbWriteEmbeded(dwIoBase, dwAL7230InitTableAMode[5]); //Reg5
        bResult &= IFRFbWriteEmbeded(dwIoBase, dwAL7230InitTableAMode[7]); //Reg7
        bResult &= IFRFbWriteEmbeded(dwIoBase, dwAL7230InitTableAMode[10]);//Reg10
        bResult &= IFRFbWriteEmbeded(dwIoBase, dwAL7230InitTableAMode[12]);//Reg12
        bResult &= IFRFbWriteEmbeded(dwIoBase, dwAL7230InitTableAMode[15]);//Reg15
    }
    else if( (byOldChannel > CB_MAX_CHANNEL_24G) && (byNewChannel <= CB_MAX_CHANNEL_24G) )
    {
        // change from 5G to 2.4G
        bResult &= IFRFbWriteEmbeded(dwIoBase, dwAL7230InitTable[2]); //Reg2
        bResult &= IFRFbWriteEmbeded(dwIoBase, dwAL7230InitTable[3]); //Reg3
        bResult &= IFRFbWriteEmbeded(dwIoBase, dwAL7230InitTable[5]); //Reg5
        bResult &= IFRFbWriteEmbeded(dwIoBase, dwAL7230InitTable[7]); //Reg7
        bResult &= IFRFbWriteEmbeded(dwIoBase, dwAL7230InitTable[10]);//Reg10
        bResult &= IFRFbWriteEmbeded(dwIoBase, dwAL7230InitTable[12]);//Reg12
        bResult &= IFRFbWriteEmbeded(dwIoBase, dwAL7230InitTable[15]);//Reg15
    }

    return bResult;
}