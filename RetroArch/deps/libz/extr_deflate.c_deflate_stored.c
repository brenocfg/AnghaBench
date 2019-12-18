#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int ulg ;
typedef  scalar_t__ uInt ;
struct TYPE_6__ {int pending_buf_size; int lookahead; scalar_t__ strstart; scalar_t__ w_size; long block_start; scalar_t__ insert; } ;
typedef  TYPE_1__ deflate_state ;
typedef  int /*<<< orphan*/  block_state ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int,char*) ; 
 int /*<<< orphan*/  FLUSH_BLOCK (TYPE_1__*,int) ; 
 scalar_t__ MAX_DIST (TYPE_1__*) ; 
 int Z_FINISH ; 
 int Z_NO_FLUSH ; 
 int /*<<< orphan*/  block_done ; 
 int /*<<< orphan*/  fill_window (TYPE_1__*) ; 
 int /*<<< orphan*/  finish_done ; 
 int /*<<< orphan*/  need_more ; 

__attribute__((used)) static block_state deflate_stored(deflate_state *s, int flush)
{
   /* Stored blocks are limited to 0xffff bytes, pending_buf is limited
    * to pending_buf_size, and each stored block has a 5 byte header:
    */
   ulg max_block_size = 0xffff;
   ulg max_start;

   if (max_block_size > s->pending_buf_size - 5) {
      max_block_size = s->pending_buf_size - 5;
   }

   /* Copy as much as possible from input to output: */
   for (;;) {
      /* Fill the window as much as possible: */
      if (s->lookahead <= 1) {

         Assert(s->strstart < s->w_size+MAX_DIST(s) ||
               s->block_start >= (long)s->w_size, "slide too late");

         fill_window(s);
         if (s->lookahead == 0 && flush == Z_NO_FLUSH) return need_more;

         if (s->lookahead == 0) break; /* flush the current block */
      }
      Assert(s->block_start >= 0L, "block gone");

      s->strstart += s->lookahead;
      s->lookahead = 0;

      /* Emit a stored block if pending_buf will be full: */
      max_start = s->block_start + max_block_size;
      if (s->strstart == 0 || (ulg)s->strstart >= max_start) {
         /* strstart == 0 is possible when wraparound on 16-bit machine */
         s->lookahead = (uInt)(s->strstart - max_start);
         s->strstart = (uInt)max_start;
         FLUSH_BLOCK(s, 0);
      }
      /* Flush if we may have to slide, otherwise block_start may become
       * negative and the data will be gone:
       */
      if (s->strstart - (uInt)s->block_start >= MAX_DIST(s)) {
         FLUSH_BLOCK(s, 0);
      }
   }
   s->insert = 0;
   if (flush == Z_FINISH) {
      FLUSH_BLOCK(s, 1);
      return finish_done;
   }
   if ((long)s->strstart > s->block_start)
      FLUSH_BLOCK(s, 0);
   return block_done;
}