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
struct MySofa {int /*<<< orphan*/  fir; int /*<<< orphan*/ * hrtf; int /*<<< orphan*/ * lookup; int /*<<< orphan*/ * neighborhood; } ;

/* Variables and functions */
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mysofa_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mysofa_lookup_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mysofa_neighborhood_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int close_sofa(struct MySofa *sofa)
{
    if (sofa->neighborhood)
        mysofa_neighborhood_free(sofa->neighborhood);
    sofa->neighborhood = NULL;
    if (sofa->lookup)
        mysofa_lookup_free(sofa->lookup);
    sofa->lookup = NULL;
    if (sofa->hrtf)
        mysofa_free(sofa->hrtf);
    sofa->hrtf = NULL;
    av_freep(&sofa->fir);

    return 0;
}