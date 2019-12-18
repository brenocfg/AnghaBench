#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_2__ {scalar_t__ pos; scalar_t__ filesize; } ;
typedef  TYPE_1__ IOContext ;

/* Variables and functions */
 scalar_t__ INT64_MAX ; 
 int SEEK_CUR ; 
 int SEEK_END ; 

__attribute__((used)) static int64_t io_seek(void *opaque, int64_t offset, int whence)
{
    IOContext *c = opaque;

    if (whence == SEEK_CUR) {
        if (offset > INT64_MAX - c->pos)
            return -1;
        offset += c->pos;
    } else if (whence == SEEK_END) {
        if (offset > INT64_MAX - c->filesize)
            return -1;
        offset += c->filesize;
    }
    if (offset < 0 || offset > c->filesize)
        return -1;
    c->pos = offset;
    return 0;
}