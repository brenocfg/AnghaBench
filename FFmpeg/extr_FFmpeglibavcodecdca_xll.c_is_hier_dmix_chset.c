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
struct TYPE_3__ {scalar_t__ hier_chset; scalar_t__ dmix_embedded; int /*<<< orphan*/  primary_chset; } ;
typedef  TYPE_1__ DCAXllChSet ;

/* Variables and functions */

__attribute__((used)) static int is_hier_dmix_chset(DCAXllChSet *c)
{
    return !c->primary_chset && c->dmix_embedded && c->hier_chset;
}