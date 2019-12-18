#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ en; } ;
struct TYPE_8__ {void* wdt_wprotect; TYPE_1__ wdt_config0; } ;
struct TYPE_6__ {scalar_t__ en; } ;
struct TYPE_7__ {void* wdt_wprotect; TYPE_2__ wdt_config0; } ;

/* Variables and functions */
 TYPE_4__ TIMERG0 ; 
 TYPE_3__ TIMERG1 ; 
 void* TIMG_WDT_WKEY_VALUE ; 

__attribute__((used)) static inline void disableAllWdts(void)
{
    TIMERG0.wdt_wprotect = TIMG_WDT_WKEY_VALUE;
    TIMERG0.wdt_config0.en = 0;
    TIMERG0.wdt_wprotect = 0;
    TIMERG1.wdt_wprotect = TIMG_WDT_WKEY_VALUE;
    TIMERG1.wdt_config0.en = 0;
    TIMERG1.wdt_wprotect = 0;
}