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
struct TYPE_4__ {int serialno; } ;
typedef  TYPE_1__ ogg_stream_state ;

/* Variables and functions */
 int OGG_SUCCESS ; 
 int /*<<< orphan*/  ogg_stream_reset (TYPE_1__*) ; 

int ogg_stream_reset_serialno(ogg_stream_state *os,int serialno){
  ogg_stream_reset(os);
  os->serialno=serialno;
  return OGG_SUCCESS;
}