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
struct TYPE_6__ {int /*<<< orphan*/  bufferpool; } ;
typedef  TYPE_1__ ogg_sync_state ;

/* Variables and functions */
 int OGG_SUCCESS ; 
 int /*<<< orphan*/  _ogg_free (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ogg_buffer_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ogg_sync_reset (TYPE_1__*) ; 

int ogg_sync_destroy(ogg_sync_state *oy){
  if(oy){
    ogg_sync_reset(oy);
    ogg_buffer_destroy(oy->bufferpool);
    memset(oy,0,sizeof(*oy));
    _ogg_free(oy);
  }
  return OGG_SUCCESS;
}