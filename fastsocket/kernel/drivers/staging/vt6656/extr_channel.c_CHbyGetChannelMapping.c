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
struct TYPE_2__ {size_t byChannelNumber; } ;
typedef  size_t BYTE ;

/* Variables and functions */
 size_t CB_MAX_CHANNEL ; 
 TYPE_1__* sChannelTbl ; 

BYTE CHbyGetChannelMapping(BYTE byChannelNumber)
{
BYTE    ii;
BYTE    byCHMapping = 0;

    for (ii=1; ii<=CB_MAX_CHANNEL; ii++ ) {
        if ( sChannelTbl[ii].byChannelNumber == byChannelNumber ) {
            byCHMapping = ii;
        }
    }
    return byCHMapping;
}