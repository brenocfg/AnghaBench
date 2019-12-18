#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ Frameskip; } ;

/* Variables and functions */
 TYPE_1__ currentConfig ; 
 int /*<<< orphan*/  sprintf (char const*,char*,scalar_t__) ; 
 char const* static_buff ; 

__attribute__((used)) static const char *mgn_opt_fskip(int id, int *offs)
{
	if (currentConfig.Frameskip < 0)
		return "Auto";
	sprintf(static_buff, "%d", currentConfig.Frameskip);
	return static_buff;
}