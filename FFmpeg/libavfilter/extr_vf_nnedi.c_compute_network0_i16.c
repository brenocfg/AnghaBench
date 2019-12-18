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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  NNEDIContext ;

/* Variables and functions */
 scalar_t__ FFMAX (float,float) ; 
 int /*<<< orphan*/  dot_prod (int /*<<< orphan*/ *,float*,float const*,float*,int,int,float*) ; 
 int /*<<< orphan*/  dot_prods (int /*<<< orphan*/ *,float const*,float const*,float*,int,int,float*) ; 
 int /*<<< orphan*/  elliott (float*,int) ; 

__attribute__((used)) static void compute_network0_i16(NNEDIContext *s, const float *inputf, const float *weightsf, uint8_t *d)
{
    const float *wf = weightsf + 2 * 48;
    float t, temp[12], scale = 1.0f;

    dot_prods(s, inputf, weightsf, temp, 4, 48, &scale);
    t = temp[0];
    elliott(temp, 4);
    temp[0] = t;
    dot_prod(s, temp, wf + 8, temp + 4, 4, 4, &scale);
    elliott(temp + 4, 4);
    dot_prod(s, temp, wf + 8 + 4 * 5, temp + 8, 4, 8, &scale);
    if (FFMAX(temp[10], temp[11]) <= FFMAX(temp[8], temp[9]))
        d[0] = 1;
    else
        d[0] = 0;
}