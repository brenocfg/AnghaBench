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
struct TYPE_4__ {int /*<<< orphan*/  submodel; } ;
typedef  TYPE_1__ sb_devc ;

/* Variables and functions */
 int es_rec_set_recmask (TYPE_1__*,int) ; 
 scalar_t__ ess_has_rec_mixer (int /*<<< orphan*/ ) ; 

int ess_set_recmask(sb_devc * devc, int *mask)
{
	/* This applies to ESS chips with record mixers only! */

	if (ess_has_rec_mixer (devc->submodel)) {
		*mask	= es_rec_set_recmask (devc, *mask);
		return 1;									/* Applied		*/
	} else {
		return 0;									/* Not applied	*/
	}
}