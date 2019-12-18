#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zdev_t ;
typedef  int u8_t ;
typedef  size_t u16_t ;
struct TYPE_7__ {size_t regDmnEnum; scalar_t__ isoName; } ;
struct TYPE_5__ {size_t regionCode; } ;
struct TYPE_6__ {TYPE_1__ regulationTable; } ;

/* Variables and functions */
 size_t N (TYPE_3__*) ; 
 TYPE_3__* allCountries ; 
 TYPE_2__* wd ; 
 int /*<<< orphan*/  zfHpGetRegulationTable (int /*<<< orphan*/ *,size_t,size_t,size_t) ; 
 scalar_t__ zfMemoryIsEqual (int*,int*,int) ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

u8_t zfHpGetRegulationTablefromISO(zdev_t* dev, u8_t *countryInfo, u8_t length)
{
    u16_t i;
    u16_t RegDomain;
    u16_t c_lo = 2000, c_hi = 6000; //default channel is all enable
    //u8_t strLen = 2;

    zmw_get_wlan_dev(dev);

    zmw_declare_for_critical_section();

    if (countryInfo[4] != 0x20)
    { // with (I)ndoor/(O)utdoor info
        //strLen = 3;
    }
    //zm_debug_msg_s("Desired iso name = ", isoName);
    for (i = 0; i < N(allCountries); i++)
    {
        //zm_debug_msg_s("Current iso name = ", allCountries[i].isoName);
        if (zfMemoryIsEqual((u8_t *)allCountries[i].isoName, (u8_t *)&countryInfo[2], length-1))
        {
            //DbgPrint("Set current iso name = %s\n", allCountries[i].isoName);
            //zm_debug_msg0("iso name hit!!");

            RegDomain = allCountries[i].regDmnEnum;

            if (wd->regulationTable.regionCode != RegDomain)
            {
                zfHpGetRegulationTable(dev, RegDomain, c_lo, c_hi);
            }

            //while (index < (countryInfo[1]+2))
            //{
            //  if (countryInfo[index] <= 14)
            //  {
            //        /* calculate 2.4GHz low boundary channel frequency */
            //        ch = countryInfo[index];
            //        if ( ch == 14 )
            //            c_lo = ZM_CH_G_14;
            //        else
            //            c_lo = ZM_CH_G_1 + (ch - 1) * 5;
            //        /* calculate 2.4GHz high boundary channel frequency */
            //        ch = countryInfo[index] + countryInfo[index + 1] - 1;
            //        if ( ch == 14 )
            //            c_hi = ZM_CH_G_14;
            //        else
            //            c_hi = ZM_CH_G_1 + (ch - 1) * 5;
            //  }
            //  else
            //  {
            //        /* calculate 5GHz low boundary channel frequency */
            //        ch = countryInfo[index];
            //        if ( (ch >= 184)&&(ch <= 196) )
            //            c_lo = 4000 + ch*5;
            //        else
            //            c_lo = 5000 + ch*5;
            //        /* calculate 5GHz high boundary channel frequency */
            //        ch = countryInfo[index] + countryInfo[index + 1] - 1;
            //        if ( (ch >= 184)&&(ch <= 196) )
            //            c_hi = 4000 + ch*5;
            //        else
            //            c_hi = 5000 + ch*5;
            //  }
            //
            //  zfHpGetRegulationTable(dev, RegDomain, c_lo, c_hi);
            //
            //  index+=3;
            //}

            return 0;
        }
    }
    //zm_debug_msg_s("Invalid iso name = ", &countryInfo[2]);
    return 1;
}