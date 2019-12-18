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
struct TYPE_4__ {int pageno; scalar_t__ granulepos; scalar_t__ packetno; scalar_t__ b_o_s; scalar_t__ e_o_s; scalar_t__ header_fill; scalar_t__ lacing_returned; scalar_t__ lacing_packet; scalar_t__ lacing_fill; scalar_t__ body_returned; scalar_t__ body_fill; } ;
typedef  TYPE_1__ ogg_stream_state ;

/* Variables and functions */
 scalar_t__ ogg_stream_check (TYPE_1__*) ; 

int ogg_stream_reset(ogg_stream_state *os){
  if(ogg_stream_check(os)) return -1;

  os->body_fill=0;
  os->body_returned=0;

  os->lacing_fill=0;
  os->lacing_packet=0;
  os->lacing_returned=0;

  os->header_fill=0;

  os->e_o_s=0;
  os->b_o_s=0;
  os->pageno=-1;
  os->packetno=0;
  os->granulepos=0;

  return(0);
}