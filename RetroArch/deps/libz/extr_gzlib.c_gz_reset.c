#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* gz_statep ;
struct TYPE_6__ {scalar_t__ avail_in; } ;
struct TYPE_7__ {scalar_t__ pos; scalar_t__ have; } ;
struct TYPE_8__ {scalar_t__ mode; TYPE_1__ strm; TYPE_2__ x; scalar_t__ seek; int /*<<< orphan*/  how; scalar_t__ past; scalar_t__ eof; } ;

/* Variables and functions */
 scalar_t__ GZ_READ ; 
 int /*<<< orphan*/  LOOK ; 
 int /*<<< orphan*/  Z_OK ; 
 int /*<<< orphan*/  gz_error (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gz_reset(gz_statep state)
{
   state->x.have = 0;              /* no output data available */
   if (state->mode == GZ_READ) {   /* for reading ... */
      state->eof = 0;             /* not at end of file */
      state->past = 0;            /* have not read past end yet */
      state->how = LOOK;          /* look for gzip header */
   }
   state->seek = 0;                /* no seek request pending */
   gz_error(state, Z_OK, NULL);    /* clear error */
   state->x.pos = 0;               /* no uncompressed data yet */
   state->strm.avail_in = 0;       /* no input data yet */
}