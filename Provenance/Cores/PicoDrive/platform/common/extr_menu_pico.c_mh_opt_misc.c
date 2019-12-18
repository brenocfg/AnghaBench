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
#define  MA_OPT_REGION 129 
#define  MA_OPT_SOUND_QUALITY 128 
 int PBTN_RIGHT ; 
 int /*<<< orphan*/  PsndRate ; 
 int /*<<< orphan*/  region_prevnext (int) ; 
 int /*<<< orphan*/  sndrate_prevnext (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mh_opt_misc(int id, int keys)
{
	switch (id) {
	case MA_OPT_SOUND_QUALITY:
		PsndRate = sndrate_prevnext(PsndRate, keys & PBTN_RIGHT);
		break;
	case MA_OPT_REGION:
		region_prevnext(keys & PBTN_RIGHT);
		break;
	default:
		break;
	}
	return 0;
}