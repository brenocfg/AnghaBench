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
struct TYPE_2__ {int /*<<< orphan*/  command; } ;

/* Variables and functions */
 scalar_t__ Q_stricmp (char const*,int /*<<< orphan*/ ) ; 
 int g_bindCount ; 
 TYPE_1__* g_bindings ; 

int BindingIDFromName(const char *name) {
	int i;
  for (i=0; i < g_bindCount; i++)
	{
		if (Q_stricmp(name, g_bindings[i].command) == 0) {
			return i;
		}
	}
	return -1;
}