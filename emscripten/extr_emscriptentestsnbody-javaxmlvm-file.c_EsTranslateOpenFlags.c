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
typedef  int I_32 ;

/* Variables and functions */
 int HyOpenAppend ; 
 int HyOpenCreate ; 
 int HyOpenCreateNew ; 
 int HyOpenRead ; 
 int HyOpenTruncate ; 
 int HyOpenWrite ; 
 int O_APPEND ; 
 int O_CREAT ; 
 int O_EXCL ; 
 int O_RDONLY ; 
 int O_RDWR ; 
 int O_TRUNC ; 
 int O_WRONLY ; 

__attribute__((used)) static I_32
EsTranslateOpenFlags (I_32 flags)
{
    I_32 realFlags = 0;
    
    if (flags & HyOpenAppend)
    {
        realFlags |= O_APPEND;
    }
    if (flags & HyOpenTruncate)
    {
        realFlags |= O_TRUNC;
    }
    if (flags & HyOpenCreate)
    {
        realFlags |= O_CREAT;
    }
    if (flags & HyOpenCreateNew)
    {
        realFlags |= O_EXCL | O_CREAT;
    }
#ifdef O_SYNC
	if (flags & HyOpenSync) {
		realFlags |= O_SYNC;
	}
#endif    
    if (flags & HyOpenRead)
    {
        if (flags & HyOpenWrite)
        {
            return (O_RDWR | realFlags);
        }
        return (O_RDONLY | realFlags);
    }
    if (flags & HyOpenWrite)
    {
        return (O_WRONLY | realFlags);
    }
    return -1;
}