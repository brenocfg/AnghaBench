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
struct TYPE_2__ {int /*<<< orphan*/ * configstrings; } ;

/* Variables and functions */
 char* AAS_StringFromIndex (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 size_t CS_MODELS ; 
 int /*<<< orphan*/  MAX_MODELS ; 
 TYPE_1__ aasworld ; 

char *AAS_ModelFromIndex(int index)
{
	return AAS_StringFromIndex("ModelFromIndex", &aasworld.configstrings[CS_MODELS], MAX_MODELS, index);
}