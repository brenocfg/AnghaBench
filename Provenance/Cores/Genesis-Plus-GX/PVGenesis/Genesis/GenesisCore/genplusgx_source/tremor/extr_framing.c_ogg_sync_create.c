#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  bufferpool; } ;
typedef  TYPE_1__ ogg_sync_state ;

/* Variables and functions */
 TYPE_1__* _ogg_calloc (int,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ogg_buffer_create () ; 

ogg_sync_state *ogg_sync_create(void){
  ogg_sync_state *oy=_ogg_calloc(1,sizeof(*oy));
  memset(oy,0,sizeof(*oy));
  oy->bufferpool=ogg_buffer_create();
  return oy;
}