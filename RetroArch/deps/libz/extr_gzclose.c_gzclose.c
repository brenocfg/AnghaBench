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
typedef  TYPE_1__* gz_statep ;
typedef  int /*<<< orphan*/ * gzFile ;
struct TYPE_2__ {scalar_t__ mode; } ;

/* Variables and functions */
 scalar_t__ GZ_READ ; 
 int Z_STREAM_ERROR ; 
 int gzclose_r (int /*<<< orphan*/ *) ; 
 int gzclose_w (int /*<<< orphan*/ *) ; 

int gzclose(gzFile file)
{
#ifndef NO_GZCOMPRESS
   gz_statep state;

   if (file == NULL)
      return Z_STREAM_ERROR;
   state = (gz_statep)file;

   return state->mode == GZ_READ ? gzclose_r(file) : gzclose_w(file);
#else
   return gzclose_r(file);
#endif
}