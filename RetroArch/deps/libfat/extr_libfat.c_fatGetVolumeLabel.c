#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ open_r; scalar_t__ deviceData; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ devoptab_t ;
struct TYPE_7__ {scalar_t__ open_r; } ;
struct TYPE_6__ {int /*<<< orphan*/  label; } ;
typedef  TYPE_2__ PARTITION ;

/* Variables and functions */
 scalar_t__ GetDeviceOpTab (char*) ; 
 int /*<<< orphan*/  _FAT_directory_getVolumeLabel (TYPE_2__*,char*) ; 
 scalar_t__ _FAT_mem_allocate (int) ; 
 int /*<<< orphan*/  _FAT_mem_free (char*) ; 
 TYPE_3__ dotab_fat ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char const*) ; 
 scalar_t__ strncasecmp (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int) ; 

void fatGetVolumeLabel (const char* name, char *label)
{
	devoptab_t *devops;
	PARTITION* partition;
	char *buf;
	int namelen,i;

	if(!name || !label)
		return;

	namelen = strlen(name);
	buf=(char*)_FAT_mem_allocate(sizeof(char)*namelen+2);
	strcpy(buf,name);

	if (name[namelen-1] == '/')
   {
		buf[namelen-1]='\0';
		namelen--;
	}

	if (name[namelen-1] != ':')
   {
		buf[namelen]=':';
		buf[namelen+1]='\0';
	}

	devops = (devoptab_t*)GetDeviceOpTab(buf);

	for(i=0;buf[i]!='\0' && buf[i]!=':';i++);
	if (!devops || strncasecmp(buf,devops->name,i))
   {
		_FAT_mem_free(buf);
		return;
	}

	_FAT_mem_free(buf);

	/* Perform a quick check to make sure we're dealing with a libfat controlled device */
	if (devops->open_r != dotab_fat.open_r)
		return;

	partition = (PARTITION*)devops->deviceData;

	if(!_FAT_directory_getVolumeLabel(partition, label))
   {
		strncpy(label,partition->label,11);
		label[11]='\0';
	}
	if(!strncmp(label, "NO NAME", 7))
      label[0]='\0';
}