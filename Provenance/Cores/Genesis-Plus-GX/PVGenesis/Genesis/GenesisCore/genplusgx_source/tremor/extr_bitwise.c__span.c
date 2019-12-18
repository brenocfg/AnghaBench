#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int headend; scalar_t__ headbit; TYPE_2__* head; scalar_t__ headptr; int /*<<< orphan*/  count; } ;
typedef  TYPE_3__ oggpack_buffer ;
struct TYPE_7__ {scalar_t__ length; scalar_t__ begin; TYPE_1__* buffer; struct TYPE_7__* next; } ;
struct TYPE_6__ {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  _adv_halt (TYPE_3__*) ; 

__attribute__((used)) static void _span(oggpack_buffer *b){
  while(b->headend<1){
    if(b->head->next){
      b->count+=b->head->length;
      b->head=b->head->next;
      b->headptr=b->head->buffer->data+b->head->begin-b->headend; 
      b->headend+=b->head->length;      
    }else{
      /* we've either met the end of decode, or gone past it. halt
         only if we're past */
      if(b->headend<0 || b->headbit)
        /* read has fallen off the end */
        _adv_halt(b);

      break;
    }
  }
}