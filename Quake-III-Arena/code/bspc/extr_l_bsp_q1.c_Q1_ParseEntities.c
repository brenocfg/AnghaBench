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
typedef  int /*<<< orphan*/  script_t ;

/* Variables and functions */
 int /*<<< orphan*/  FreeScript (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * LoadScriptMemory (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ParseEntity (int /*<<< orphan*/ *) ; 
 int SCFL_NOSTRINGESCAPECHARS ; 
 int SCFL_NOSTRINGWHITESPACES ; 
 int /*<<< orphan*/  SetScriptFlags (int /*<<< orphan*/ *,int) ; 
 scalar_t__ num_entities ; 
 int /*<<< orphan*/  q1_dentdata ; 
 int /*<<< orphan*/  q1_entdatasize ; 

void Q1_ParseEntities (void)
{
	script_t *script;

	num_entities = 0;
	script = LoadScriptMemory(q1_dentdata, q1_entdatasize, "*Quake1 bsp file");
	SetScriptFlags(script, SCFL_NOSTRINGWHITESPACES |
									SCFL_NOSTRINGESCAPECHARS);

	while(ParseEntity(script))
	{
	} //end while

	FreeScript(script);
}