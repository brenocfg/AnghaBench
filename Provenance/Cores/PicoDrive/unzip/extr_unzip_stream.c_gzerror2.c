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
struct TYPE_2__ {int z_err; } ;
typedef  TYPE_1__ gz_stream ;
typedef  scalar_t__ gzFile ;

/* Variables and functions */
 int Z_STREAM_ERROR ; 

int gzerror2(gzFile file)
{
    gz_stream *s = (gz_stream*)file;

    if (s == NULL)
        return Z_STREAM_ERROR;

    return s->z_err;
}