#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  (* Print ) (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {TYPE_1__* scriptstack; } ;
struct TYPE_4__ {int /*<<< orphan*/  filename; } ;

/* Variables and functions */
 int MAX_SOURCEFILES ; 
 int /*<<< orphan*/  PRT_ERROR ; 
 TYPE_3__ botimport ; 
 TYPE_2__** sourceFiles ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void PC_CheckOpenSourceHandles(void)
{
	int i;

	for (i = 1; i < MAX_SOURCEFILES; i++)
	{
		if (sourceFiles[i])
		{
#ifdef BOTLIB
			botimport.Print(PRT_ERROR, "file %s still open in precompiler\n", sourceFiles[i]->scriptstack->filename);
#endif	//BOTLIB
		} //end if
	} //end for
}