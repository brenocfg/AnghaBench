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
struct TYPE_4__ {int recmask; int /*<<< orphan*/  submodel; } ;
typedef  TYPE_1__ sb_devc ;

/* Variables and functions */
 int ES_REC_MIXER_RECDIFF ; 
 scalar_t__ ess_has_rec_mixer (int /*<<< orphan*/ ) ; 
 int sb_common_mixer_set (TYPE_1__*,int,int,int) ; 

int ess_mixer_set(sb_devc *devc, int dev, int left, int right)
{
	if (ess_has_rec_mixer (devc->submodel) && (devc->recmask & (1 << dev))) {
		sb_common_mixer_set (devc, dev + ES_REC_MIXER_RECDIFF, left, right);
	}
	return sb_common_mixer_set (devc, dev, left, right);
}