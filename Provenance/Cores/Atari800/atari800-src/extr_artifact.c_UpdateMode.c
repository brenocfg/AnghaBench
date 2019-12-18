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
typedef  int ARTIFACT_t ;

/* Variables and functions */
 int /*<<< orphan*/  ANTIC_UpdateArtifacting () ; 
 int ANTIC_artif_mode ; 
 int ANTIC_artif_new ; 
 int ANTIC_pal_blending ; 
 int ARTIFACT_NTSC_FULL ; 
 int ARTIFACT_NTSC_NEW ; 
 int ARTIFACT_NTSC_OLD ; 
 int ARTIFACT_PAL_BLEND ; 
 int ARTIFACT_PAL_SIMPLE ; 
 int ARTIFACT_mode ; 
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  VIDEOMODE_Update () ; 

__attribute__((used)) static void UpdateMode(int old_mode, int reinit)
{
#if (NTSC_FILTER && SUPPORTS_CHANGE_VIDEOMODE) || defined(PAL_BLENDING)
	int need_reinit = FALSE;
#endif /* (NTSC_FILTER && SUPPORTS_CHANGE_VIDEOMODE) || defined(PAL_BLENDING) */
	if (ARTIFACT_mode == old_mode)
		return;

	/* TV effect has changed. */
#if NTSC_FILTER && SUPPORTS_CHANGE_VIDEOMODE
	/* If switched between non-filter and NTSC filter, video mode needs update. */
	if (ARTIFACT_mode == ARTIFACT_NTSC_FULL ||
	    old_mode == ARTIFACT_NTSC_FULL)
		need_reinit = TRUE;
#endif /* NTSC_FILTER && SUPPORTS_CHANGE_VIDEOMODE */
#ifdef PAL_BLENDING
	/* If PAL blending was enabled/disabled, video mode needs update. */
	if (ARTIFACT_mode == ARTIFACT_PAL_BLEND ||
	    old_mode == ARTIFACT_PAL_BLEND)
		need_reinit = TRUE;
#endif /* PAL_BLENDING */
#ifndef NO_SIMPLE_PAL_BLENDING
	ANTIC_pal_blending = ARTIFACT_mode == ARTIFACT_PAL_SIMPLE;
#endif /* NO_SIMPLE_PAL_BLENDING */
	if (ARTIFACT_mode != ARTIFACT_NTSC_OLD &&
	    ARTIFACT_mode != ARTIFACT_NTSC_NEW) {
		ANTIC_artif_new = ANTIC_artif_mode = 0;
	} else {
		if (ANTIC_artif_mode == 0)
			/* ANTIC new or old artifacting is being enabled */
			ANTIC_artif_mode = 1;
		ANTIC_artif_new = ARTIFACT_mode == ARTIFACT_NTSC_NEW;
	}
	ANTIC_UpdateArtifacting();
#if SUPPORTS_CHANGE_VIDEOMODE
	if (need_reinit && reinit) {
		if (!VIDEOMODE_Update()) {
			ARTIFACT_t tmp = ARTIFACT_mode;
			/* Updating display failed, restore previous setting. */
			ARTIFACT_mode = old_mode;
			UpdateMode(tmp, FALSE);
		}
	}
#endif /* SUPPORTS_CHANGE_VIDEOMODE */
}