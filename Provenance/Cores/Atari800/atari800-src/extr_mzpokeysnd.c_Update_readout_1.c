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
struct TYPE_3__ {int /*<<< orphan*/  readout_1; scalar_t__ c1sw4; scalar_t__ c1vo; } ;
typedef  TYPE_1__ PokeyState ;

/* Variables and functions */
 int /*<<< orphan*/  readout1_hipass ; 
 int /*<<< orphan*/  readout1_normal ; 
 int /*<<< orphan*/  readout1_vo ; 

__attribute__((used)) static void Update_readout_1(PokeyState* ps)
{
    if(ps->c1vo)
        ps->readout_1 = readout1_vo;
    else if(ps->c1sw4)
        ps->readout_1 = readout1_hipass;
    else
        ps->readout_1 = readout1_normal;
}