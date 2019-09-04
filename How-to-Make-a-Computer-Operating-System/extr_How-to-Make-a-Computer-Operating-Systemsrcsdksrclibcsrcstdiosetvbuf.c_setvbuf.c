#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int flags; char* buffer; size_t buffer_size; scalar_t__ buffer_data_size; scalar_t__ buffer_pos; } ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 int __FILE_DONTFREEBUF ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (size_t) ; 
 int set_flags (TYPE_1__*,int) ; 

int setvbuf( FILE* stream, char* buf, int flags, size_t size ) {
    if ( buf != NULL ) {
        if ( ( stream->flags & __FILE_DONTFREEBUF ) == 0 ) {
            free( stream->buffer );
        }

        stream->buffer = buf;
        stream->flags |= __FILE_DONTFREEBUF;
    } else {
        char *tmp;

        if ( size == 0 ) {
            return set_flags( stream, flags );
        }

        tmp = ( char* )malloc( size );

        if ( tmp == NULL ) {
            return -1;
        }

        if ( ( stream->flags & __FILE_DONTFREEBUF ) == 0 ) {
            free( stream->buffer );
        }

        stream->buffer = tmp;
        stream->flags &= ~__FILE_DONTFREEBUF;
    }

    stream->buffer_size = size;
    stream->buffer_pos = 0;
    stream->buffer_data_size = 0;

    return set_flags( stream, flags );
}