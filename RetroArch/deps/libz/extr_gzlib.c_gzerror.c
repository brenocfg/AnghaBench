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
struct TYPE_2__ {scalar_t__ mode; int err; char const* msg; } ;

/* Variables and functions */
 scalar_t__ GZ_READ ; 
 scalar_t__ GZ_WRITE ; 
 int Z_MEM_ERROR ; 

const char * gzerror(gzFile file, int *errnum)
{
   gz_statep state;

   /* get internal structure and check integrity */
   if (file == NULL)
      return NULL;
   state = (gz_statep)file;
   if (state->mode != GZ_READ && state->mode != GZ_WRITE)
      return NULL;

   /* return error information */
   if (errnum != NULL)
      *errnum = state->err;
   return state->err == Z_MEM_ERROR ? "out of memory" :
      (state->msg == NULL ? "" : state->msg);
}