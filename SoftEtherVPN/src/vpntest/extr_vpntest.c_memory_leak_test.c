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
typedef  int /*<<< orphan*/  UINT ;

/* Variables and functions */
 char* Malloc (int) ; 
 int /*<<< orphan*/  Print (char*) ; 

void memory_leak_test(UINT num, char **arg)
{
	char *a = Malloc(1);

	Print("Hello, I am the great dictator of this kingdom!\n");
	Print("Just now I called Malloc(1) and never free! Ha ha ha !!\n");
}