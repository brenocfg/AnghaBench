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
typedef  int off_t ;
struct TYPE_3__ {int flags; int buffer_data_size; int buffer_pos; int has_ungotten; int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_CUR ; 
 int __FILE_BUFINPUT ; 
 int __FILE_EOF ; 
 int __FILE_ERROR ; 
 int lseek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

off_t ftello( FILE* stream ) {
    off_t l;

    if ( stream->flags & ( __FILE_EOF | __FILE_ERROR ) ) {
        return -1;
    }

    l = lseek( stream->fd, 0, SEEK_CUR );

    if ( l == ( off_t )-1 ) {
        return -1;
    }

    if ( stream->flags & __FILE_BUFINPUT ) {
        return l - ( stream->buffer_data_size - stream->buffer_pos ) - stream->has_ungotten;
    } else {
        return l + stream->buffer_pos;
    }
}