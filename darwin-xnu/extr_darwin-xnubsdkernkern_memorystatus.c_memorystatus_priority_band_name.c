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
typedef  int int32_t ;

/* Variables and functions */
#define  JETSAM_PRIORITY_AUDIO_AND_ACCESSORY 134 
#define  JETSAM_PRIORITY_CONDUCTOR 133 
#define  JETSAM_PRIORITY_CRITICAL 132 
#define  JETSAM_PRIORITY_EXECUTIVE 131 
#define  JETSAM_PRIORITY_FOREGROUND 130 
#define  JETSAM_PRIORITY_HOME 129 
#define  JETSAM_PRIORITY_IMPORTANT 128 

__attribute__((used)) static const char *
memorystatus_priority_band_name(int32_t priority)
{
	switch (priority) {
	case JETSAM_PRIORITY_FOREGROUND:
		return "FOREGROUND";
	case JETSAM_PRIORITY_AUDIO_AND_ACCESSORY:
		return "AUDIO_AND_ACCESSORY";
	case JETSAM_PRIORITY_CONDUCTOR:
		return "CONDUCTOR";
	case JETSAM_PRIORITY_HOME:
		return "HOME";
	case JETSAM_PRIORITY_EXECUTIVE:
		return "EXECUTIVE";
	case JETSAM_PRIORITY_IMPORTANT:
		return "IMPORTANT";
	case JETSAM_PRIORITY_CRITICAL:
		return "CRITICAL";
	}

	return ("?");
}