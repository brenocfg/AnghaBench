#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */

__attribute__((used)) static int
constrain_rgb(double * const r,
              double * const g,
              double * const b)
{
/*----------------------------------------------------------------------------
    If  the  requested RGB shade contains a negative weight for one of
    the primaries, it lies outside the color  gamut  accessible  from
    the  given  triple  of  primaries.  Desaturate it by adding white,
    equal quantities of R, G, and B, enough to make RGB all positive.
-----------------------------------------------------------------------------*/
    double w;

    /* Amount of white needed is w = - min(0, *r, *g, *b) */
    w = (0 < *r) ? 0 : *r;
    w = (w < *g) ? w : *g;
    w = (w < *b) ? w : *b;
    w = - w;

    /* Add just enough white to make r, g, b all positive. */
    if (w > 0) {
        *r += w;  *g += w; *b += w;

        return 1;                     /* Color modified to fit RGB gamut */
    }

    return 0;                         /* Color within RGB gamut */
}