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
typedef  int dtrace_stability_t ;

/* Variables and functions */
#define  DTRACE_STABILITY_EVOLVING 135 
#define  DTRACE_STABILITY_EXTERNAL 134 
#define  DTRACE_STABILITY_INTERNAL 133 
#define  DTRACE_STABILITY_OBSOLETE 132 
#define  DTRACE_STABILITY_PRIVATE 131 
#define  DTRACE_STABILITY_STABLE 130 
#define  DTRACE_STABILITY_STANDARD 129 
#define  DTRACE_STABILITY_UNSTABLE 128 

const char *
dtrace_stability_name(dtrace_stability_t s)
{
	switch (s) {
	case DTRACE_STABILITY_INTERNAL:	return ("Internal");
	case DTRACE_STABILITY_PRIVATE:	return ("Private");
	case DTRACE_STABILITY_OBSOLETE:	return ("Obsolete");
	case DTRACE_STABILITY_EXTERNAL:	return ("External");
	case DTRACE_STABILITY_UNSTABLE:	return ("Unstable");
	case DTRACE_STABILITY_EVOLVING:	return ("Evolving");
	case DTRACE_STABILITY_STABLE:	return ("Stable");
	case DTRACE_STABILITY_STANDARD:	return ("Standard");
	default:			return (NULL);
	}
}