#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int ulg ;
struct TYPE_5__ {int window_size; int w_size; size_t level; long block_start; scalar_t__ ins_h; scalar_t__ match_available; scalar_t__ prev_length; scalar_t__ match_length; scalar_t__ insert; scalar_t__ lookahead; scalar_t__ strstart; int /*<<< orphan*/  max_chain_length; int /*<<< orphan*/  nice_match; int /*<<< orphan*/  good_match; int /*<<< orphan*/  max_lazy_match; } ;
typedef  TYPE_1__ deflate_state ;
struct TYPE_6__ {int /*<<< orphan*/  max_chain; int /*<<< orphan*/  nice_length; int /*<<< orphan*/  good_length; int /*<<< orphan*/  max_lazy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR_HASH (TYPE_1__*) ; 
 scalar_t__ MIN_MATCH ; 
 TYPE_3__* configuration_table ; 
 int /*<<< orphan*/  match_init () ; 

__attribute__((used)) static void lm_init (deflate_state *s)
{
   s->window_size = (ulg)2L*s->w_size;

   CLEAR_HASH(s);

   /* Set the default configuration parameters:
   */
   s->max_lazy_match   = configuration_table[s->level].max_lazy;
   s->good_match       = configuration_table[s->level].good_length;
   s->nice_match       = configuration_table[s->level].nice_length;
   s->max_chain_length = configuration_table[s->level].max_chain;

   s->strstart = 0;
   s->block_start = 0L;
   s->lookahead = 0;
   s->insert = 0;
   s->match_length = s->prev_length = MIN_MATCH-1;
   s->match_available = 0;
   s->ins_h = 0;
#ifndef FASTEST
#ifdef ASMV
   match_init(); /* initialize the asm code */
#endif
#endif
}