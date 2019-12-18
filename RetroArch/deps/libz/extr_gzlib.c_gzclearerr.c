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
typedef  TYPE_1__* gz_statep ;
typedef  int /*<<< orphan*/ * gzFile ;
struct TYPE_3__ {scalar_t__ mode; scalar_t__ past; scalar_t__ eof; } ;

/* Variables and functions */
 scalar_t__ GZ_READ ; 
 scalar_t__ GZ_WRITE ; 
 int /*<<< orphan*/  Z_OK ; 
 int /*<<< orphan*/  gz_error (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void gzclearerr(gzFile file)
{
   gz_statep state;

   /* get internal structure and check integrity */
   if (file == NULL)
      return;
   state = (gz_statep)file;
   if (state->mode != GZ_READ && state->mode != GZ_WRITE)
      return;

   /* clear error and end-of-file */
   if (state->mode == GZ_READ) {
      state->eof = 0;
      state->past = 0;
   }
   gz_error(state, Z_OK, NULL);
}