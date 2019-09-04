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
 float F_LFTG_ALPHA ; 
 float F_LFTG_BETA ; 
 float F_LFTG_DELTA ; 
 float F_LFTG_GAMMA ; 
 int F_LFTG_K ; 
 float F_LFTG_X ; 
 int /*<<< orphan*/  extend97_float (float*,int,int) ; 

__attribute__((used)) static void sr_1d97_float(float *p, int i0, int i1)
{
    int i;

    if (i1 <= i0 + 1) {
        if (i0 == 1)
            p[1] *= F_LFTG_K/2;
        else
            p[0] *= F_LFTG_X;
        return;
    }

    extend97_float(p, i0, i1);

    for (i = (i0 >> 1) - 1; i < (i1 >> 1) + 2; i++)
        p[2 * i]     -= F_LFTG_DELTA * (p[2 * i - 1] + p[2 * i + 1]);
    /* step 4 */
    for (i = (i0 >> 1) - 1; i < (i1 >> 1) + 1; i++)
        p[2 * i + 1] -= F_LFTG_GAMMA * (p[2 * i]     + p[2 * i + 2]);
    /*step 5*/
    for (i = (i0 >> 1); i < (i1 >> 1) + 1; i++)
        p[2 * i]     += F_LFTG_BETA  * (p[2 * i - 1] + p[2 * i + 1]);
    /* step 6 */
    for (i = (i0 >> 1); i < (i1 >> 1); i++)
        p[2 * i + 1] += F_LFTG_ALPHA * (p[2 * i]     + p[2 * i + 2]);
}