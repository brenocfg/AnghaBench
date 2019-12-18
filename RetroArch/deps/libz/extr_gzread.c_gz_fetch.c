#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* z_streamp ;
typedef  TYPE_3__* gz_statep ;
struct TYPE_8__ {scalar_t__ have; int /*<<< orphan*/  next; } ;
struct TYPE_9__ {int avail_out; int /*<<< orphan*/  next_out; scalar_t__ avail_in; } ;
struct TYPE_10__ {int how; int size; int /*<<< orphan*/  out; TYPE_1__ x; int /*<<< orphan*/  eof; TYPE_2__ strm; } ;

/* Variables and functions */
#define  LOOK 130 
#define  MODE_COPY 129 
#define  MODE_GZIP 128 
 int gz_decomp (TYPE_3__*) ; 
 int gz_load (TYPE_3__*,int /*<<< orphan*/ ,int,scalar_t__*) ; 
 int gz_look (TYPE_3__*) ; 

__attribute__((used)) static int gz_fetch(gz_statep state)
{
   z_streamp strm = &(state->strm);

   do {
      switch(state->how) {
         case LOOK:      /* -> LOOK, MODE_COPY (only if never GZIP), or MODE_GZIP */
            if (gz_look(state) == -1)
               return -1;
            if (state->how == LOOK)
               return 0;
            break;
         case MODE_COPY:      /* -> MODE_COPY */
            if (gz_load(state, state->out, state->size << 1, &(state->x.have))
                  == -1)
               return -1;
            state->x.next = state->out;
            return 0;
         case MODE_GZIP:      /* -> GZIP or LOOK (if end of gzip stream) */
            strm->avail_out = state->size << 1;
            strm->next_out = state->out;
            if (gz_decomp(state) == -1)
               return -1;
      }
   } while (state->x.have == 0 && (!state->eof || strm->avail_in));
   return 0;
}