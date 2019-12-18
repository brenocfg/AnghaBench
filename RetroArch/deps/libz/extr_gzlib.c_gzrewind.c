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
struct TYPE_3__ {scalar_t__ mode; scalar_t__ err; int /*<<< orphan*/  start; int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 scalar_t__ GZ_READ ; 
 int LSEEK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ Z_BUF_ERROR ; 
 scalar_t__ Z_OK ; 
 int /*<<< orphan*/  gz_reset (TYPE_1__*) ; 

int gzrewind(gzFile file)
{
   gz_statep state;

   /* get internal structure */
   if (file == NULL)
      return -1;
   state = (gz_statep)file;

   /* check that we're reading and that there's no error */
   if (state->mode != GZ_READ ||
         (state->err != Z_OK && state->err != Z_BUF_ERROR))
      return -1;

   /* back up and start over */
   if (LSEEK(state->fd, state->start, SEEK_SET) == -1)
      return -1;
   gz_reset(state);
   return 0;
}