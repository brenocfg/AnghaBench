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
typedef  int /*<<< orphan*/  qev_t ;
struct TYPE_3__ {size_t qeend; int /*<<< orphan*/  curtick; int /*<<< orphan*/ * qet; int /*<<< orphan*/ * qev; } ;
typedef  TYPE_1__ PokeyState ;

/* Variables and functions */
 size_t filter_size ; 

__attribute__((used)) static void add_change(PokeyState* ps, qev_t a)
{
    ps->qev[ps->qeend] = a;
    ps->qet[ps->qeend] = ps->curtick; /*0;*/
    ++ps->qeend;
    if(ps->qeend >= filter_size)
        ps->qeend = 0;
}