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
typedef  int /*<<< orphan*/  entity_t ;

/* Variables and functions */
 int /*<<< orphan*/  Error (char*) ; 
 int MAX_SWITCHED_LIGHTS ; 
 scalar_t__ Q_strncasecmp (char const*,char*,int) ; 
 int /*<<< orphan*/  SetKeyValue (int /*<<< orphan*/ *,char*,char*) ; 
 char* ValueForKey (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * entities ; 
 int num_entities ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  strcmp (char*,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 

void SetLightStyles (void)
{
	int		stylenum;
	const char	*t;
	entity_t	*e;
	int		i, j;
	char	value[10];
	char	lighttargets[MAX_SWITCHED_LIGHTS][64];


	// any light that is controlled (has a targetname)
	// must have a unique style number generated for it

	stylenum = 0;
	for (i=1 ; i<num_entities ; i++)
	{
		e = &entities[i];

		t = ValueForKey (e, "classname");
		if (Q_strncasecmp (t, "light", 5))
			continue;
		t = ValueForKey (e, "targetname");
		if (!t[0])
			continue;
		
		// find this targetname
		for (j=0 ; j<stylenum ; j++)
			if (!strcmp (lighttargets[j], t))
				break;
		if (j == stylenum)
		{
			if (stylenum == MAX_SWITCHED_LIGHTS)
				Error ("stylenum == MAX_SWITCHED_LIGHTS");
			strcpy (lighttargets[j], t);
			stylenum++;
		}
		sprintf (value, "%i", 32 + j);
		SetKeyValue (e, "style", value);
	}

}