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
struct TYPE_3__ {int /*<<< orphan*/  rcbaAreap; int /*<<< orphan*/  rcbaArea; int /*<<< orphan*/  hpet2bus; int /*<<< orphan*/  bus2hpet; int /*<<< orphan*/  hpet2tsc; int /*<<< orphan*/  tsc2hpet; int /*<<< orphan*/  hpetCvtn2t; int /*<<< orphan*/  hpetCvtt2n; } ;
typedef  TYPE_1__ hpetInfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  bus2hpet ; 
 int /*<<< orphan*/  hpet2bus ; 
 int /*<<< orphan*/  hpet2tsc ; 
 int /*<<< orphan*/  hpetArea ; 
 int /*<<< orphan*/  hpetAreap ; 
 int /*<<< orphan*/  hpetCvtn2t ; 
 int /*<<< orphan*/  hpetCvtt2n ; 
 int /*<<< orphan*/  tsc2hpet ; 

void
hpet_get_info(hpetInfo_t *info)
{
    info->hpetCvtt2n = hpetCvtt2n;
    info->hpetCvtn2t = hpetCvtn2t;
    info->tsc2hpet   = tsc2hpet;
    info->hpet2tsc   = hpet2tsc;
    info->bus2hpet   = bus2hpet;
    info->hpet2bus   = hpet2bus;
    /*
     * XXX
     * We're repurposing the rcbaArea so we can use the HPET.
     * Eventually we'll rename this correctly.
     */
    info->rcbaArea   = hpetArea;
    info->rcbaAreap  = hpetAreap;
}