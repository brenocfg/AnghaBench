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
struct TYPE_4__ {int /*<<< orphan*/  indexessetup; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* Print ) (int /*<<< orphan*/ ,char*,char*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  PRT_ERROR ; 
 TYPE_2__ aasworld ; 
 TYPE_1__ botimport ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,char*,char*,int) ; 

char *AAS_StringFromIndex(char *indexname, char *stringindex[], int numindexes, int index)
{
	if (!aasworld.indexessetup)
	{
		botimport.Print(PRT_ERROR, "%s: index %d not setup\n", indexname, index);
		return "";
	} //end if
	if (index < 0 || index >= numindexes)
	{
		botimport.Print(PRT_ERROR, "%s: index %d out of range\n", indexname, index);
		return "";
	} //end if
	if (!stringindex[index])
	{
		if (index)
		{
			botimport.Print(PRT_ERROR, "%s: reference to unused index %d\n", indexname, index);
		} //end if
		return "";
	} //end if
	return stringindex[index];
}