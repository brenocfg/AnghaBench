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
 long MA_BREAK ; 
 long MA_EXEC ; 
 long MA_PHYS ; 
 long MA_READ ; 
 long MA_SHARED ; 
 long MA_STACK ; 
 long MA_WRITE ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static char *
mappingflags (long flags)
{
  static char asciiflags[8];

  strcpy (asciiflags, "-------");
#if defined (MA_PHYS)
  if (flags & MA_PHYS)
    asciiflags[0] = 'd';
#endif
  if (flags & MA_STACK)
    asciiflags[1] = 's';
  if (flags & MA_BREAK)
    asciiflags[2] = 'b';
  if (flags & MA_SHARED)
    asciiflags[3] = 's';
  if (flags & MA_READ)
    asciiflags[4] = 'r';
  if (flags & MA_WRITE)
    asciiflags[5] = 'w';
  if (flags & MA_EXEC)
    asciiflags[6] = 'x';
  return (asciiflags);
}