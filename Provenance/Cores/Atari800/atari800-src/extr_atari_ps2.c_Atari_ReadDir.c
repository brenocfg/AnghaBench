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
struct TYPE_4__ {int hour; int month; int day; int year; int sec; } ;
struct TYPE_5__ {int attrFile; TYPE_1__ _modify; scalar_t__ fileSizeByte; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ mcTable ;

/* Variables and functions */
 int FALSE ; 
 int MC_ATTR_SUBDIR ; 
 int MC_ATTR_WRITEABLE ; 
 int TRUE ; 
 int /*<<< orphan*/  Util_catpath (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dir_i ; 
 scalar_t__ dir_n ; 
 int /*<<< orphan*/  dir_path ; 
 TYPE_2__* mcDir ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int,int,int,int,char) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 

int Atari_ReadDir(char *fullpath, char *filename, int *isdir,
                  int *readonly, int *size, char *timetext)
{
	const mcTable *p;
	if (dir_i >= dir_n)
		return FALSE;
	p = mcDir + dir_i;
	if (fullpath != NULL)
		Util_catpath(fullpath, dir_path, p->name);
	if (filename != NULL)
		strcpy(filename, p->name);
	if (isdir != NULL)
		*isdir = (p->attrFile & MC_ATTR_SUBDIR) ? TRUE : FALSE;
	if (readonly != NULL)
		*readonly = (p->attrFile & MC_ATTR_WRITEABLE) ? FALSE : TRUE; // XXX: MC_ATTR_PROTECTED ?
	if (size != NULL)
		*size = (int) (p->fileSizeByte);
	if (timetext != NULL) {
		// FIXME: adjust from GMT to local time
		int hour = p->_modify.hour;
		char ampm = 'a';
		if (hour >= 12) {
			hour -= 12;
			ampm = 'p';
		}
		if (hour == 0)
			hour = 12;
		sprintf(timetext, "%2d-%02d-%02d %2d:%02d%c",
			p->_modify.month, p->_modify.day, p->_modify.year % 100, hour, p->_modify.sec, ampm);
	}
	dir_i++;
	return TRUE;
}