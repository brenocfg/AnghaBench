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
typedef  size_t ESI ;

/* Variables and functions */
 size_t SI_COUNT ; 
 size_t SI_NONE ; 

inline const char* ESI_Name(ESI esi)
{
	static const char * const names[] =
	{
		"<none>",
		"Gamepad",
		"Zapper",
		"Power Pad A",
		"Power Pad B",
		"Arkanoid Paddle",
		"Subor Mouse",
		"SNES Pad",
		"SNES Mouse"
	};

	if(esi >= SI_NONE && esi <= SI_COUNT)
		return names[esi];
	else return "<invalid ESI>";
}