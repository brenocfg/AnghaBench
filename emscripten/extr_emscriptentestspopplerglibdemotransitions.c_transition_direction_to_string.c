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
typedef  scalar_t__ PopplerPageTransitionDirection ;

/* Variables and functions */
 scalar_t__ POPPLER_PAGE_TRANSITION_INWARD ; 

__attribute__((used)) static const gchar *
transition_direction_to_string (PopplerPageTransitionDirection direction)
{
	return direction == POPPLER_PAGE_TRANSITION_INWARD ? "Inward" : "Outward";
}