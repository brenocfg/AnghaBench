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
typedef  size_t u16_t ;
struct TYPE_3__ {size_t regDmnEnum; char const* isoName; } ;

/* Variables and functions */
 size_t N (TYPE_1__*) ; 
 TYPE_1__* allCountries ; 

const char* zfHpGetisoNamefromregionCode(zdev_t* dev, u16_t regionCode)
{
    u16_t i;

    for (i = 0; i < N(allCountries); i++)
    {
        if (allCountries[i].regDmnEnum == regionCode)
        {
            return allCountries[i].isoName;
        }
    }
    /* no matching item, return default */
    return allCountries[0].isoName;
}