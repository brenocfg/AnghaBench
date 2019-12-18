#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* z_streamp ;
struct TYPE_8__ {size_t level; int strategy; scalar_t__ pending; int /*<<< orphan*/  max_chain_length; int /*<<< orphan*/  nice_match; int /*<<< orphan*/  good_match; int /*<<< orphan*/  max_lazy_match; } ;
typedef  TYPE_2__ deflate_state ;
typedef  int /*<<< orphan*/  compress_func ;
struct TYPE_9__ {int /*<<< orphan*/  max_chain; int /*<<< orphan*/  nice_length; int /*<<< orphan*/  good_length; int /*<<< orphan*/  max_lazy; int /*<<< orphan*/  func; } ;
struct TYPE_7__ {scalar_t__ total_in; struct TYPE_7__* state; } ;

/* Variables and functions */
 int /*<<< orphan*/  Z_BLOCK ; 
 int Z_BUF_ERROR ; 
 int Z_DEFAULT_COMPRESSION ; 
 int Z_FIXED ; 
 TYPE_1__* Z_NULL ; 
 int Z_OK ; 
 int Z_STREAM_ERROR ; 
 TYPE_5__* configuration_table ; 
 int deflate (TYPE_1__*,int /*<<< orphan*/ ) ; 

int deflateParams(z_streamp strm, int level, int strategy)
{
   deflate_state *s;
   compress_func func;
   int err = Z_OK;

   if (strm == Z_NULL || strm->state == Z_NULL) return Z_STREAM_ERROR;
   s = (deflate_state*)strm->state;

#ifdef FASTEST
   if (level != 0) level = 1;
#else
   if (level == Z_DEFAULT_COMPRESSION) level = 6;
#endif
   if (level < 0 || level > 9 || strategy < 0 || strategy > Z_FIXED) {
      return Z_STREAM_ERROR;
   }
   func = configuration_table[s->level].func;

   if ((strategy != s->strategy || func != configuration_table[level].func) &&
         strm->total_in != 0) {
      /* Flush the last buffer: */
      err = deflate(strm, Z_BLOCK);
      if (err == Z_BUF_ERROR && s->pending == 0)
         err = Z_OK;
   }
   if (s->level != level) {
      s->level = level;
      s->max_lazy_match   = configuration_table[level].max_lazy;
      s->good_match       = configuration_table[level].good_length;
      s->nice_match       = configuration_table[level].nice_length;
      s->max_chain_length = configuration_table[level].max_chain;
   }
   s->strategy = strategy;
   return err;
}