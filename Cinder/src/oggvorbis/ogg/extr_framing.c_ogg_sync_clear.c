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
struct TYPE_4__ {scalar_t__ data; } ;
typedef  TYPE_1__ ogg_sync_state ;

/* Variables and functions */
 int /*<<< orphan*/  _ogg_free (scalar_t__) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

int ogg_sync_clear(ogg_sync_state *oy){
  if(oy){
    if(oy->data)_ogg_free(oy->data);
    memset(oy,0,sizeof(*oy));
  }
  return(0);
}