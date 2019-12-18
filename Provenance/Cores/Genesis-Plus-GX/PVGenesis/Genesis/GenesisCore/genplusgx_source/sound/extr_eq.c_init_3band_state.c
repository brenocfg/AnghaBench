#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {double lg; double mg; double hg; int lf; int hf; } ;
typedef  TYPE_1__ EQSTATE ;

/* Variables and functions */
 double M_PI ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int sin (double) ; 

void init_3band_state(EQSTATE * es, int lowfreq, int highfreq, int mixfreq)
{
    /* Clear state */

    memset(es, 0, sizeof(EQSTATE));

    /* Set Low/Mid/High gains to unity */

    es->lg = 1.0;
    es->mg = 1.0;
    es->hg = 1.0;

    /* Calculate filter cutoff frequencies */

    es->lf = 2 * sin(M_PI * ((double) lowfreq / (double) mixfreq));
    es->hf = 2 * sin(M_PI * ((double) highfreq / (double) mixfreq));
}