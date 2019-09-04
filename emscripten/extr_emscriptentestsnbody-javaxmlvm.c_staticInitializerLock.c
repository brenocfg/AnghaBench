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
struct __TIB_DEFINITION_TEMPLATE {char* className; } ;
struct TYPE_2__ {int /*<<< orphan*/  initMutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  lockOrExit (char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* staticInitializerController ; 

void staticInitializerLock(void* tibDefinition)
{
    char* className = ((struct __TIB_DEFINITION_TEMPLATE*)tibDefinition)->className;
    lockOrExit(className, staticInitializerController->initMutex);
}