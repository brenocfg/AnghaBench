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
struct TYPE_2__ {scalar_t__ mode; int past; } ;

/* Variables and functions */
 scalar_t__ GZ_READ ; 
 scalar_t__ GZ_WRITE ; 

int gzeof(gzFile file)
{
   gz_statep state;

   /* get internal structure and check integrity */
   if (file == NULL)
      return 0;
   state = (gz_statep)file;
   if (state->mode != GZ_READ && state->mode != GZ_WRITE)
      return 0;

   /* return end-of-file state */
   return state->mode == GZ_READ ? state->past : 0;
}