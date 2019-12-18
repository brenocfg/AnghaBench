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
struct TYPE_3__ {scalar_t__ bodybytes; scalar_t__ headerbytes; scalar_t__ unsynced; scalar_t__ fifo_fill; scalar_t__ fifo_head; scalar_t__ fifo_tail; } ;
typedef  TYPE_1__ ogg_sync_state ;

/* Variables and functions */
 int OGG_SUCCESS ; 
 int /*<<< orphan*/  ogg_buffer_release (scalar_t__) ; 

int ogg_sync_reset(ogg_sync_state *oy){

  ogg_buffer_release(oy->fifo_tail);
  oy->fifo_tail=0;
  oy->fifo_head=0;
  oy->fifo_fill=0;

  oy->unsynced=0;
  oy->headerbytes=0;
  oy->bodybytes=0;
  return OGG_SUCCESS;
}