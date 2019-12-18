#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int size; int /*<<< orphan*/  handle; int /*<<< orphan*/  filepos; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  lseek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* lumpinfo ; 
 scalar_t__ malloc (int) ; 
 int numlumps ; 
 int /*<<< orphan*/  read (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  strncasecmp (int /*<<< orphan*/ ,char*,int) ; 

void*
loadlump
( char*		lumpname,
  int*		size )
{

    int		i;
    void*	lump;

    for (i=0 ; i<numlumps ; i++)
    {
	if (!strncasecmp(lumpinfo[i].name, lumpname, 8))
	    break;
    }

    if (i == numlumps)
    {
	// fprintf(stderr,
	//   "Could not find lumpname [%s]\n", lumpname);
	lump = 0;
    }
    else
    {
	lump = (void *) malloc(lumpinfo[i].size);
	lseek(lumpinfo[i].handle, lumpinfo[i].filepos, SEEK_SET);
	read(lumpinfo[i].handle, lump, lumpinfo[i].size);
	*size = lumpinfo[i].size;
    }

    return lump;

}