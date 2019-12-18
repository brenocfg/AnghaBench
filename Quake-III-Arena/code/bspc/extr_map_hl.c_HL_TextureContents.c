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
 int CONTENTS_LAVA ; 
 int CONTENTS_SLIME ; 
 int CONTENTS_SOLID ; 
 int CONTENTS_WATER ; 
 int /*<<< orphan*/  Q_strncasecmp (char*,char*,int) ; 

int HL_TextureContents(char *name)
{
	if (!Q_strncasecmp (name, "sky",3))
		return CONTENTS_SOLID;

	if (!Q_strncasecmp(name+1,"!lava",5))
		return CONTENTS_LAVA;

	if (!Q_strncasecmp(name+1,"!slime",6))
		return CONTENTS_SLIME;

	/*
	if (!Q_strncasecmp (name, "!cur_90",7))
		return CONTENTS_CURRENT_90;
	if (!Q_strncasecmp (name, "!cur_0",6))
		return CONTENTS_CURRENT_0;
	if (!Q_strncasecmp (name, "!cur_270",8))
		return CONTENTS_CURRENT_270;
	if (!Q_strncasecmp (name, "!cur_180",8))
		return CONTENTS_CURRENT_180;
	if (!Q_strncasecmp (name, "!cur_up",7))
		return CONTENTS_CURRENT_UP;
	if (!Q_strncasecmp (name, "!cur_dwn",8))
		return CONTENTS_CURRENT_DOWN;
	//*/
	if (name[0] == '!')
		return CONTENTS_WATER;
	/*
	if (!Q_strncasecmp (name, "origin",6))
		return CONTENTS_ORIGIN;
	if (!Q_strncasecmp (name, "clip",4))
		return CONTENTS_CLIP;
	if( !Q_strncasecmp( name, "translucent", 11 ) )
		return CONTENTS_TRANSLUCENT;
	if( name[0] == '@' )
		return CONTENTS_TRANSLUCENT;
	//*/

	return CONTENTS_SOLID;
}