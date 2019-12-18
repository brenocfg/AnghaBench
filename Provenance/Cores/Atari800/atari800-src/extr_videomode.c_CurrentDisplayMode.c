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
typedef  int /*<<< orphan*/  VIDEOMODE_MODE_t ;

/* Variables and functions */
 scalar_t__ AF80_enabled ; 
 scalar_t__ ARTIFACT_NTSC_FULL ; 
 scalar_t__ ARTIFACT_mode ; 
 scalar_t__ PBI_PROTO80_enabled ; 
 scalar_t__ VIDEOMODE_80_column ; 
 int /*<<< orphan*/  VIDEOMODE_MODE_AF80 ; 
 int /*<<< orphan*/  VIDEOMODE_MODE_NORMAL ; 
 int /*<<< orphan*/  VIDEOMODE_MODE_NTSC_FILTER ; 
 int /*<<< orphan*/  VIDEOMODE_MODE_PROTO80 ; 
 int /*<<< orphan*/  VIDEOMODE_MODE_XEP80 ; 
 scalar_t__ XEP80_enabled ; 
 int /*<<< orphan*/  force_standard_screen ; 

__attribute__((used)) static VIDEOMODE_MODE_t CurrentDisplayMode(void)
{
#if COLUMN_80
	if (!force_standard_screen && VIDEOMODE_80_column) {
#ifdef XEP80_EMULATION
		if (XEP80_enabled)
			return VIDEOMODE_MODE_XEP80;
#endif
#ifdef PBI_PROTO80
		if (PBI_PROTO80_enabled)
			return VIDEOMODE_MODE_PROTO80;
#endif
#ifdef AF80
		if (AF80_enabled)
			return VIDEOMODE_MODE_AF80;
#endif
	}
#endif /* COLUMN_80 */
#if NTSC_FILTER
	if (ARTIFACT_mode == ARTIFACT_NTSC_FULL)
		return VIDEOMODE_MODE_NTSC_FILTER;
#endif
	return VIDEOMODE_MODE_NORMAL;
}