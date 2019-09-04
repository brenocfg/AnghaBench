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
typedef  int /*<<< orphan*/  off_t ;
struct TYPE_4__ {int flags; int /*<<< orphan*/  fd; scalar_t__ has_ungotten; scalar_t__ buffer_data_size; scalar_t__ buffer_pos; } ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 int __FILE_EOF ; 
 int __FILE_ERROR ; 
 int /*<<< orphan*/  fflush (TYPE_1__*) ; 
 int lseek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int fseeko( FILE* stream, off_t offset, int whence ) {
    fflush( stream );

    stream->buffer_pos = 0;
    stream->buffer_data_size = 0;
    stream->flags &= ~( __FILE_EOF | __FILE_ERROR );
    stream->has_ungotten = 0;

    return ( lseek( stream->fd, offset, whence ) != -1 ? 0 : -1 );
}