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
typedef  char gchar ;
typedef  int PopplerPageTransitionType ;

/* Variables and functions */
#define  POPPLER_PAGE_TRANSITION_BLINDS 139 
#define  POPPLER_PAGE_TRANSITION_BOX 138 
#define  POPPLER_PAGE_TRANSITION_COVER 137 
#define  POPPLER_PAGE_TRANSITION_DISSOLVE 136 
#define  POPPLER_PAGE_TRANSITION_FADE 135 
#define  POPPLER_PAGE_TRANSITION_FLY 134 
#define  POPPLER_PAGE_TRANSITION_GLITTER 133 
#define  POPPLER_PAGE_TRANSITION_PUSH 132 
#define  POPPLER_PAGE_TRANSITION_REPLACE 131 
#define  POPPLER_PAGE_TRANSITION_SPLIT 130 
#define  POPPLER_PAGE_TRANSITION_UNCOVER 129 
#define  POPPLER_PAGE_TRANSITION_WIPE 128 

__attribute__((used)) static const gchar *
transition_type_to_string (PopplerPageTransitionType type)
{
	switch (type) {
	case POPPLER_PAGE_TRANSITION_REPLACE:
		return "Replace";
	case POPPLER_PAGE_TRANSITION_SPLIT:
		return "Split";
	case POPPLER_PAGE_TRANSITION_BLINDS:
		return "Blinds";
	case POPPLER_PAGE_TRANSITION_BOX:
		return "Box";
	case POPPLER_PAGE_TRANSITION_WIPE:
		return "Wipe";
	case POPPLER_PAGE_TRANSITION_DISSOLVE:
		return "Dissolve";
	case POPPLER_PAGE_TRANSITION_GLITTER:
		return "Glitter";
	case POPPLER_PAGE_TRANSITION_FLY:
		return "Fly";
	case POPPLER_PAGE_TRANSITION_PUSH:
		return "Push";
	case POPPLER_PAGE_TRANSITION_COVER:
		return "Cover";
	case POPPLER_PAGE_TRANSITION_UNCOVER:
		return "Uncover";
	case POPPLER_PAGE_TRANSITION_FADE:
		return "Fade";
	}

	return "Unknown";
}