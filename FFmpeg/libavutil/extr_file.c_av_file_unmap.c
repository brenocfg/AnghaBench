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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  UnmapViewOfFile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  munmap (int /*<<< orphan*/ *,size_t) ; 

void av_file_unmap(uint8_t *bufptr, size_t size)
{
    if (!size || !bufptr)
        return;
#if HAVE_MMAP
    munmap(bufptr, size);
#elif HAVE_MAPVIEWOFFILE
    UnmapViewOfFile(bufptr);
#else
    av_free(bufptr);
#endif
}