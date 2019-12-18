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
struct TYPE_3__ {int /*<<< orphan*/  readout_3; scalar_t__ c3vo; } ;
typedef  TYPE_1__ PokeyState ;

/* Variables and functions */
 int /*<<< orphan*/  readout3_normal ; 
 int /*<<< orphan*/  readout3_vo ; 

__attribute__((used)) static void Update_readout_3(PokeyState* ps)
{
    if(ps->c3vo)
        ps->readout_3 = readout3_vo;
    else
        ps->readout_3 = readout3_normal;
}