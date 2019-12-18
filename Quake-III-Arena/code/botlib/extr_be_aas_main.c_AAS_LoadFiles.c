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
struct TYPE_4__ {int /*<<< orphan*/  filename; int /*<<< orphan*/  mapname; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* Print ) (int /*<<< orphan*/ ,char*,char*) ;} ;

/* Variables and functions */
 int AAS_LoadAASFile (char*) ; 
 int /*<<< orphan*/  AAS_LoadBSPFile () ; 
 int /*<<< orphan*/  AAS_ResetEntityLinks () ; 
 int BLERR_NOERROR ; 
 int /*<<< orphan*/  Com_sprintf (char*,int,char*,char const*) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  PRT_MESSAGE ; 
 TYPE_2__ aasworld ; 
 TYPE_1__ botimport ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,char*) ; 

int AAS_LoadFiles(const char *mapname)
{
	int errnum;
	char aasfile[MAX_PATH];
//	char bspfile[MAX_PATH];

	strcpy(aasworld.mapname, mapname);
	//NOTE: first reset the entity links into the AAS areas and BSP leaves
	// the AAS link heap and BSP link heap are reset after respectively the
	// AAS file and BSP file are loaded
	AAS_ResetEntityLinks();
	// load bsp info
	AAS_LoadBSPFile();

	//load the aas file
	Com_sprintf(aasfile, MAX_PATH, "maps/%s.aas", mapname);
	errnum = AAS_LoadAASFile(aasfile);
	if (errnum != BLERR_NOERROR)
		return errnum;

	botimport.Print(PRT_MESSAGE, "loaded %s\n", aasfile);
	strncpy(aasworld.filename, aasfile, MAX_PATH);
	return BLERR_NOERROR;
}