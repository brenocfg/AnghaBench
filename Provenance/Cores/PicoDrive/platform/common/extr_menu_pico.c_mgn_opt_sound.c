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
 int POPT_EN_STEREO ; 
 int PicoOpt ; 
 int PsndRate ; 
 int /*<<< orphan*/  sprintf (char const*,char*,int,char const*) ; 
 char const* static_buff ; 

__attribute__((used)) static const char *mgn_opt_sound(int id, int *offs)
{
	const char *str2;
	*offs = -8;
	str2 = (PicoOpt & POPT_EN_STEREO) ? "stereo" : "mono";
	sprintf(static_buff, "%5iHz %s", PsndRate, str2);
	return static_buff;
}