#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int flags; struct TYPE_5__* buffer; int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 int __FILE_DONTFREEBUF ; 
 int close (int /*<<< orphan*/ ) ; 
 int fflush (TYPE_1__*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

int fclose( FILE* stream ) {
    int result;

    result = fflush( stream );
    result |= close( stream->fd );

    if ( ( ( stream->flags & __FILE_DONTFREEBUF ) == 0 ) &&
         ( stream->buffer != NULL ) ) {
        free( stream->buffer );
    }

    free( stream );

    return result;
}