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
struct TYPE_4__ {int flags; char unget_buffer; scalar_t__ has_ungotten; } ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 int EOF ; 
 int __FILE_CAN_READ ; 
 int __FILE_ERROR ; 
 int fgetc (TYPE_1__*) ; 

size_t fread( void* ptr, size_t size, size_t nmemb, FILE* stream ) {
    int res;
    unsigned long i, j;

    j = size * nmemb;
    i = 0;

    if ( ( stream->flags & __FILE_CAN_READ ) == 0 ) {
        stream->flags |= __FILE_ERROR;
        return 0;
    }

    if ( ( j == 0 ) ||
         ( ( j / nmemb ) != size ) ) {
        return 0;
    }

    if ( stream->has_ungotten ) {
        stream->has_ungotten = 0;
        *( char* )ptr = stream->unget_buffer;
        ++i;

        if ( j == 1 ) {
            return 1;
        }
    }

    for ( ; i < j; ++i ) {
        res = fgetc( stream );

        if ( res == EOF ) {
            return i / size;
        } else {
            ( ( unsigned char* )ptr )[ i ] = ( unsigned char )res;
        }
    }

    return nmemb;
}