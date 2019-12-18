#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* animname; int /*<<< orphan*/  contents; int /*<<< orphan*/  flags; int /*<<< orphan*/  value; } ;
typedef  TYPE_1__ miptex_t ;
struct TYPE_5__ {char* name; char* animname; void* contents; void* flags; void* value; } ;

/* Variables and functions */
 int /*<<< orphan*/  Error (char*) ; 
 int /*<<< orphan*/  FreeMemory (TYPE_1__*) ; 
 void* LittleLong (int /*<<< orphan*/ ) ; 
 int MAX_MAP_TEXTURES ; 
 int TryLoadFile (char*,void**) ; 
 char* gamedir ; 
 int nummiptex ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 TYPE_2__* textureref ; 

int FindMiptex (char *name)
{
	int i;
	char path[1024];
	miptex_t	*mt;

	for (i = 0; i < nummiptex; i++)
	{
		if (!strcmp (name, textureref[i].name))
		{
			return i;
		} //end if
	} //end for
	if (nummiptex == MAX_MAP_TEXTURES)
		Error ("MAX_MAP_TEXTURES");
	strcpy (textureref[i].name, name);

	// load the miptex to get the flags and values
	sprintf (path, "%stextures/%s.wal", gamedir, name);
	if (TryLoadFile (path, (void **)&mt) != -1)
	{
		textureref[i].value = LittleLong (mt->value);
		textureref[i].flags = LittleLong (mt->flags);
		textureref[i].contents = LittleLong (mt->contents);
		strcpy (textureref[i].animname, mt->animname);
		FreeMemory(mt);
	} //end if
	nummiptex++;

	if (textureref[i].animname[0])
		FindMiptex (textureref[i].animname);

	return i;
}