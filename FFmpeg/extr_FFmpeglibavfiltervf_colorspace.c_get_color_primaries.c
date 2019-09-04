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
struct TYPE_2__ {int /*<<< orphan*/  xr; } ;
struct ColorPrimaries {TYPE_1__ coeff; } ;
typedef  enum AVColorPrimaries { ____Placeholder_AVColorPrimaries } AVColorPrimaries ;

/* Variables and functions */
 int AVCOL_PRI_NB ; 
 struct ColorPrimaries* color_primaries ; 

__attribute__((used)) static const struct ColorPrimaries *get_color_primaries(enum AVColorPrimaries prm)
{
    const struct ColorPrimaries *p;

    if (prm >= AVCOL_PRI_NB)
        return NULL;
    p = &color_primaries[prm];
    if (!p->coeff.xr)
        return NULL;

    return p;
}