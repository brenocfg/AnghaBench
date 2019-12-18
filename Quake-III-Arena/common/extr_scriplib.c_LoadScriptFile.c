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
 int /*<<< orphan*/  AddScriptToStack (char const*) ; 
 void* endofscript ; 
 void* qfalse ; 
 int /*<<< orphan*/  script ; 
 int /*<<< orphan*/  scriptstack ; 
 void* tokenready ; 

void LoadScriptFile( const char *filename ) {
	script = scriptstack;
	AddScriptToStack (filename);

	endofscript = qfalse;
	tokenready = qfalse;
}