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
struct TYPE_5__ {int flags; int buffer_pos; int buffer_size; int* buffer; int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 int EOF ; 
 int __FILE_BUFLINEWISE ; 
 int __FILE_CAN_WRITE ; 
 int __FILE_ERROR ; 
 int __FILE_NOBUF ; 
 scalar_t__ __set_stream_flags (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ fflush (TYPE_1__*) ; 
 int write (int /*<<< orphan*/ ,int*,int) ; 

int fputc( int c, FILE* stream ) {
    /* Check if we can write to the stream */

    if ( ( ( stream->flags & __FILE_CAN_WRITE ) == 0 ) ||
         ( __set_stream_flags( stream, 0 ) ) ) {
        stream->flags |= __FILE_ERROR;
        return EOF;
    }

    /* Make sure we have free space in the buffer */

    if ( stream->buffer_pos >= stream->buffer_size - 1 ) {
        if ( fflush( stream ) ) {
            stream->flags |= __FILE_ERROR;
            return EOF;
        }
    }

    if ( stream->flags & __FILE_NOBUF ) {
        if ( write( stream->fd, &c, 1 ) != 1 ) {
            stream->flags |= __FILE_ERROR;
            return EOF;
        }

        return 0;
    }

    stream->buffer[ stream->buffer_pos++ ] = c;

    if ( ( ( stream->flags & __FILE_BUFLINEWISE ) && ( c == '\n' ) ) ||
         ( stream->flags & __FILE_NOBUF ) ) {
        if ( fflush( stream ) ) {
            stream->flags |= __FILE_ERROR;
            return EOF;
        }
    }

    return 0;
}