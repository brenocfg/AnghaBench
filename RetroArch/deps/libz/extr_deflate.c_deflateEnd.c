#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  struct internal_state_deflate* z_streamp ;
struct internal_state_deflate {int status; int /*<<< orphan*/  window; int /*<<< orphan*/  prev; int /*<<< orphan*/  head; int /*<<< orphan*/  pending_buf; struct internal_state_deflate* state; } ;

/* Variables and functions */
 int BUSY_STATE ; 
 int COMMENT_STATE ; 
 int EXTRA_STATE ; 
 int FINISH_STATE ; 
 int HCRC_STATE ; 
 int INIT_STATE ; 
 int NAME_STATE ; 
 int /*<<< orphan*/  TRY_FREE (struct internal_state_deflate*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZFREE (struct internal_state_deflate*,struct internal_state_deflate*) ; 
 int Z_DATA_ERROR ; 
 struct internal_state_deflate* Z_NULL ; 
 int Z_OK ; 
 int Z_STREAM_ERROR ; 

int deflateEnd (z_streamp strm)
{
   struct internal_state_deflate *state;
   int status;

   if (strm == Z_NULL || strm->state == Z_NULL) return Z_STREAM_ERROR;
   state = (struct internal_state_deflate*)strm->state;

   status = state->status;
   if (status != INIT_STATE &&
         status != EXTRA_STATE &&
         status != NAME_STATE &&
         status != COMMENT_STATE &&
         status != HCRC_STATE &&
         status != BUSY_STATE &&
         status != FINISH_STATE) {
      return Z_STREAM_ERROR;
   }

   /* Deallocate in reverse order of allocations: */
   TRY_FREE(strm, state->pending_buf);
   TRY_FREE(strm, state->head);
   TRY_FREE(strm, state->prev);
   TRY_FREE(strm, state->window);

   ZFREE(strm, state);
   state = Z_NULL;

   return status == BUSY_STATE ? Z_DATA_ERROR : Z_OK;
}