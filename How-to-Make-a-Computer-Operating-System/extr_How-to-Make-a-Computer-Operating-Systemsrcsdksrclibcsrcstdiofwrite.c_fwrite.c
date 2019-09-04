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
typedef  size_t ssize_t ;
struct TYPE_5__ {int flags; unsigned long buffer_size; int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 int __FILE_CAN_WRITE ; 
 int __FILE_ERROR ; 
 int __FILE_NOBUF ; 
 scalar_t__ fflush (TYPE_1__*) ; 
 scalar_t__ fputc (unsigned char const,TYPE_1__*) ; 
 size_t write (int /*<<< orphan*/ ,void const*,unsigned long) ; 

size_t fwrite( const void* ptr, size_t size, size_t nmemb, FILE* stream ) {
    ssize_t res;
    unsigned long len=size * nmemb;
    long i;

    if ( ( stream->flags & __FILE_CAN_WRITE ) == 0 ) {
        stream->flags |= __FILE_ERROR;
        return 0;
    }

    if ( ( nmemb == 0 ) ||
         ( ( len / nmemb ) != size ) ) {
        return 0;
    }

    if ( ( len > stream->buffer_size ) || ( stream->flags & __FILE_NOBUF ) ) {
        if ( fflush( stream ) ) {
            return 0;
        }

        res = write( stream->fd, ptr, len );
    } else {
        register const unsigned char* c = ptr;

        for ( i = len; i > 0; --i, ++c ) {
            if ( fputc( *c, stream ) ) {
                res = len - i;
                goto abort;
            }
        }

        res = len;
    }

    if ( res < 0 ) {
        stream->flags |= __FILE_ERROR;
        return 0;
    }

abort:
    return size ? res / size : 0;
}