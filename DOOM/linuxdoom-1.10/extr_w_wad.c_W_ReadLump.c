#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int handle; int size; int /*<<< orphan*/  position; } ;
typedef  TYPE_1__ lumpinfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  I_Error (char*,int,...) ; 
 int O_BINARY ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* lumpinfo ; 
 int numlumps ; 
 int open (int /*<<< orphan*/ ,int) ; 
 int read (int,void*,int) ; 
 int /*<<< orphan*/  reloadname ; 

void
W_ReadLump
( int		lump,
  void*		dest )
{
    int		c;
    lumpinfo_t*	l;
    int		handle;
	
    if (lump >= numlumps)
	I_Error ("W_ReadLump: %i >= numlumps",lump);

    l = lumpinfo+lump;
	
    // ??? I_BeginRead ();
	
    if (l->handle == -1)
    {
	// reloadable file, so use open / read / close
	if ( (handle = open (reloadname,O_RDONLY | O_BINARY)) == -1)
	    I_Error ("W_ReadLump: couldn't open %s",reloadname);
    }
    else
	handle = l->handle;
		
    lseek (handle, l->position, SEEK_SET);
    c = read (handle, dest, l->size);

    if (c < l->size)
	I_Error ("W_ReadLump: only read %i of %i on lump %i",
		 c,l->size,lump);	

    if (l->handle == -1)
	close (handle);
		
    // ??? I_EndRead ();
}