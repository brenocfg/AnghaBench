#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* z_streamp ;
struct internal_state_deflate {int wrap; int /*<<< orphan*/  gzhead; } ;
typedef  int /*<<< orphan*/  gz_headerp ;
struct TYPE_4__ {struct TYPE_4__* state; } ;

/* Variables and functions */
 TYPE_1__* Z_NULL ; 
 int Z_OK ; 
 int Z_STREAM_ERROR ; 

int deflateSetHeader (z_streamp strm, gz_headerp head)
{
   struct internal_state_deflate *state = (struct internal_state_deflate*)strm->state;
   if (strm == Z_NULL || strm->state == Z_NULL) return Z_STREAM_ERROR;
   if (state->wrap != 2)
      return Z_STREAM_ERROR;
   state->gzhead = head;
   return Z_OK;
}