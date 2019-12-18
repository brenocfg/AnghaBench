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
struct TYPE_3__ {int /*<<< orphan*/  (* Print ) (int /*<<< orphan*/ ,char*,char*,char*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  PRT_ERROR ; 
 int /*<<< orphan*/  Q_stricmp (char*,char*) ; 
 TYPE_2__ aasworld ; 
 TYPE_1__ botimport ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,char*,char*) ; 

int AAS_IndexFromString(char *indexname, char *stringindex[], int numindexes, char *string)
{
	int i;
	if (!aasworld.indexessetup)
	{
		botimport.Print(PRT_ERROR, "%s: index not setup \"%s\"\n", indexname, string);
		return 0;
	} //end if
	for (i = 0; i < numindexes; i++)
	{
		if (!stringindex[i]) continue;
		if (!Q_stricmp(stringindex[i], string)) return i;
	} //end for
	return 0;
}