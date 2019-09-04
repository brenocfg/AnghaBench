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
struct TYPE_3__ {int flags; scalar_t__ buffer_pos; scalar_t__ buffer_data_size; scalar_t__ has_ungotten; } ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 int __FILE_BUFINPUT ; 
 int __FILE_NOBUF ; 

int fpurge( FILE* stream ) {
    if ( stream->flags & __FILE_NOBUF ) {
        return 0;
    }

    stream->has_ungotten = 0;

    if ( stream->flags & __FILE_BUFINPUT ) {
        stream->buffer_pos = stream->buffer_data_size;
    } else {
        stream->buffer_pos = 0;
    }

    return 0;
}