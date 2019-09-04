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
struct TYPE_4__ {int flags; } ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 int __FILE_BUFINPUT ; 
 int fflush (TYPE_1__*) ; 

int __set_stream_flags( FILE* stream, int new_flags ) {
    if ( ( stream->flags & __FILE_BUFINPUT ) != new_flags) {
        int error;

        error = fflush( stream );

        stream->flags = ( stream->flags & ~__FILE_BUFINPUT ) | new_flags;

        return error;
    }

    return 0;
}