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
typedef  int /*<<< orphan*/  oggbyte_buffer ;
struct TYPE_3__ {int body_fill_next; scalar_t__ laceptr; scalar_t__ lacing_fill; int clearflag; } ;
typedef  TYPE_1__ ogg_stream_state ;

/* Variables and functions */
 int FINFLAG ; 
 int oggbyte_read1 (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void _next_lace(oggbyte_buffer *ob,ogg_stream_state *os){
  /* search ahead one lace */
  os->body_fill_next=0;
  while(os->laceptr<os->lacing_fill){
    int val=oggbyte_read1(ob,27+os->laceptr++);
    os->body_fill_next+=val;
    if(val<255){
      os->body_fill_next|=FINFLAG;
      os->clearflag=1;
      break;
    }
  }
}