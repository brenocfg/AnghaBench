#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* gz_statep ;
typedef  int /*<<< orphan*/ * gzFile ;
struct TYPE_5__ {int have; unsigned char* next; int /*<<< orphan*/  pos; } ;
struct TYPE_6__ {scalar_t__ mode; scalar_t__ err; unsigned char* out; int size; scalar_t__ past; TYPE_1__ x; int /*<<< orphan*/  skip; scalar_t__ seek; } ;

/* Variables and functions */
 scalar_t__ GZ_READ ; 
 scalar_t__ Z_BUF_ERROR ; 
 int /*<<< orphan*/  Z_DATA_ERROR ; 
 scalar_t__ Z_OK ; 
 int /*<<< orphan*/  gz_error (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int gz_skip (TYPE_2__*,int /*<<< orphan*/ ) ; 

int gzungetc(int c, gzFile file)
{
   gz_statep state;

   /* get internal structure */
   if (file == NULL)
      return -1;
   state = (gz_statep)file;

   /* check that we're reading and that there's no (serious) error */
   if (state->mode != GZ_READ ||
         (state->err != Z_OK && state->err != Z_BUF_ERROR))
      return -1;

   /* process a skip request */
   if (state->seek) {
      state->seek = 0;
      if (gz_skip(state, state->skip) == -1)
         return -1;
   }

   /* can't push EOF */
   if (c < 0)
      return -1;

   /* if output buffer empty, put byte at end (allows more pushing) */
   if (state->x.have == 0) {
      state->x.have = 1;
      state->x.next = state->out + (state->size << 1) - 1;
      state->x.next[0] = c;
      state->x.pos--;
      state->past = 0;
      return c;
   }

   /* if no room, give up (must have already done a gzungetc()) */
   if (state->x.have == (state->size << 1)) {
      gz_error(state, Z_DATA_ERROR, "out of room to push characters");
      return -1;
   }

   /* slide output data if needed and insert byte before existing data */
   if (state->x.next == state->out) {
      unsigned char *src = state->out + state->x.have;
      unsigned char *dest = state->out + (state->size << 1);
      while (src > state->out)
         *--dest = *--src;
      state->x.next = dest;
   }
   state->x.have++;
   state->x.next--;
   state->x.next[0] = c;
   state->x.pos--;
   state->past = 0;
   return c;
}