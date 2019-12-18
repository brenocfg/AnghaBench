#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zdev_t ;
typedef  int /*<<< orphan*/  u8_t ;
typedef  size_t u16_t ;
struct TYPE_3__ {size_t regDmnEnum; scalar_t__ isoName; } ;

/* Variables and functions */
 size_t DEF_REGDMN ; 
 size_t N (TYPE_1__*) ; 
 TYPE_1__* allCountries ; 
 scalar_t__ zfMemoryIsEqual (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

u16_t zfHpGetRegionCodeFromIsoName(zdev_t* dev, u8_t *countryIsoName)
{
    u16_t i;
    u16_t regionCode;

    /* if no matching item, return default */
    regionCode = DEF_REGDMN;

    for (i = 0; i < N(allCountries); i++)
    {
        if (zfMemoryIsEqual((u8_t *)allCountries[i].isoName, countryIsoName, 2))
        {
            regionCode = allCountries[i].regDmnEnum;
            break;
        }
    }

    return regionCode;
}