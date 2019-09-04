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
struct TYPE_3__ {scalar_t__ subband_num_actual; scalar_t__ level; scalar_t__ subband_num; } ;
typedef  TYPE_1__ CFHDContext ;

/* Variables and functions */

__attribute__((used)) static void init_plane_defaults(CFHDContext *s)
{
    s->subband_num        = 0;
    s->level              = 0;
    s->subband_num_actual = 0;
}