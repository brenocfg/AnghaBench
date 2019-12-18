#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  size; int /*<<< orphan*/  filepos; int /*<<< orphan*/  name; int /*<<< orphan*/  infotableofs; int /*<<< orphan*/  numlumps; int /*<<< orphan*/  identification; } ;
typedef  TYPE_1__ wadinfo_t ;
struct TYPE_7__ {int handle; void* size; void* filepos; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ lumpinfo_t ;
typedef  TYPE_1__ filelump_t ;

/* Variables and functions */
 void* LONG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  derror (char*) ; 
 int /*<<< orphan*/  lseek (int,int,int /*<<< orphan*/ ) ; 
 TYPE_2__* lumpinfo ; 
 scalar_t__ malloc (int) ; 
 int numlumps ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read (int,TYPE_1__*,int) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void openwad(char* wadname)
{

    int		wadfile;
    int		tableoffset;
    int		tablelength;
    int		tablefilelength;
    int		i;
    wadinfo_t	header;
    filelump_t*	filetable;

    // open and read the wadfile header
    wadfile = open(wadname, O_RDONLY);

    if (wadfile < 0)
	derror("Could not open wadfile");

    read(wadfile, &header, sizeof header);

    if (strncmp(header.identification, "IWAD", 4))
	derror("wadfile has weirdo header");

    numlumps = LONG(header.numlumps);
    tableoffset = LONG(header.infotableofs);
    tablelength = numlumps * sizeof(lumpinfo_t);
    tablefilelength = numlumps * sizeof(filelump_t);
    lumpinfo = (lumpinfo_t *) malloc(tablelength);
    filetable = (filelump_t *) ((char*)lumpinfo + tablelength - tablefilelength);

    // get the lumpinfo table
    lseek(wadfile, tableoffset, SEEK_SET);
    read(wadfile, filetable, tablefilelength);

    // process the table to make the endianness right and shift it down
    for (i=0 ; i<numlumps ; i++)
    {
	strncpy(lumpinfo[i].name, filetable[i].name, 8);
	lumpinfo[i].handle = wadfile;
	lumpinfo[i].filepos = LONG(filetable[i].filepos);
	lumpinfo[i].size = LONG(filetable[i].size);
	// fprintf(stderr, "lump [%.8s] exists\n", lumpinfo[i].name);
    }

}