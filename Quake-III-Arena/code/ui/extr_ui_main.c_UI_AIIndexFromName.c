#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int aliasCount; TYPE_1__* aliasList; } ;
struct TYPE_3__ {int /*<<< orphan*/  ai; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ Q_stricmp (int /*<<< orphan*/ ,char const*) ; 
 int const UI_AIIndex (int /*<<< orphan*/ ) ; 
 TYPE_2__ uiInfo ; 

__attribute__((used)) static const int UI_AIIndexFromName(const char *name) {
	int j;
	for (j = 0; j < uiInfo.aliasCount; j++) {
		if (Q_stricmp(uiInfo.aliasList[j].name, name) == 0) {
			return UI_AIIndex(uiInfo.aliasList[j].ai);
		}
	}
	return 0;
}