#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int /*<<< orphan*/  RA0; } ;
typedef  TYPE_1__ scudspregs_struct ;

/* Variables and functions */
 int /*<<< orphan*/  dsp_dma03 (TYPE_1__*,int /*<<< orphan*/ ) ; 

void dsp_dma07(scudspregs_struct *sc, u32 inst)
{
    u32 saveRa0 = sc->RA0;
    dsp_dma03(sc, inst);
    sc->RA0 = saveRa0;

}