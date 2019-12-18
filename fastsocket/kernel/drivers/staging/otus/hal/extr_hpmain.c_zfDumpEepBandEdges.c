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
typedef  size_t u8_t ;
struct ar5416Eeprom {TYPE_1__* ctlData; int /*<<< orphan*/ * ctlIndex; } ;
struct TYPE_2__ {int /*<<< orphan*/ ** ctlEdges; } ;

/* Variables and functions */
 size_t AR5416_NUM_BAND_EDGES ; 
 size_t AR5416_NUM_CTLS ; 
 int /*<<< orphan*/  zm_dbg (char*) ; 

void zfDumpEepBandEdges(struct ar5416Eeprom* eepromImage)
{
    #ifdef ZM_ENABLE_BANDEDGES_WINDOWS_DEBUG
    u8_t i, j, k;

#if 0
    zm_dbg(("\n === BandEdges index dump ==== \n"));

    for (i = 0; i < AR5416_NUM_CTLS; i++)
    {
        zm_dbg(("%02x ", eepromImage->ctlIndex[i]));
    }

    zm_dbg(("\n === BandEdges data dump ==== \n"));

    for (i = 0; i < AR5416_NUM_CTLS; i++)
    {
        for (j = 0; j < 2; j++)
        {
            for(k = 0; k < AR5416_NUM_BAND_EDGES; k++)
            {
                u8_t *pdata = (u8_t*)&(eepromImage->ctlData[i].ctlEdges[j][k]);
                zm_dbg(("(%02x %02x)", pdata[0], pdata[1]));
            }
            zm_dbg(("\n"));
        }
    }
#else
    zm_dbg(("\n === BandEdges index dump ==== \n"));
    for (i = 0; i < 24; i+=8)
    {
        zm_dbg(("%02x %02x %02x %02x %02x %02x %02x %02x",
               eepromImage->ctlIndex[i+0], eepromImage->ctlIndex[i+1], eepromImage->ctlIndex[i+2], eepromImage->ctlIndex[i+3],
               eepromImage->ctlIndex[i+4], eepromImage->ctlIndex[i+5], eepromImage->ctlIndex[i+6], eepromImage->ctlIndex[i+7]
               ));
    }

    zm_dbg(("\n === BandEdges data dump ==== \n"));

    for (i = 0; i < AR5416_NUM_CTLS; i++)
    {
        for (j = 0; j < 2; j++)
        {
            u8_t *pdata = (u8_t*)&(eepromImage->ctlData[i].ctlEdges[j]);
            zm_dbg(("(%03d %02x) (%03d %02x) (%03d %02x) (%03d %02x) \n",
                   pdata[0], pdata[1], pdata[2], pdata[3],
                   pdata[4], pdata[5], pdata[6], pdata[7]
                   ));
            zm_dbg(("(%03d %02x) (%03d %02x) (%03d %02x) (%03d %02x) \n",
                   pdata[8], pdata[9], pdata[10], pdata[11],
                   pdata[12], pdata[13], pdata[14], pdata[15]
                   ));
        }
    }
#endif
    #endif
}