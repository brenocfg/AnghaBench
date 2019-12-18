#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int end; int pos; TYPE_2__* ref; scalar_t__ ptr; } ;
typedef  TYPE_3__ oggbyte_buffer ;
struct TYPE_6__ {int length; scalar_t__ begin; TYPE_1__* buffer; struct TYPE_6__* next; } ;
struct TYPE_5__ {scalar_t__ data; } ;

/* Variables and functions */

__attribute__((used)) static void _positionF(oggbyte_buffer *b,int pos){
  /* scan forward for position */
  while(pos>=b->end){
    /* just seek forward */
    b->pos+=b->ref->length;
    b->ref=b->ref->next;
    b->end=b->ref->length+b->pos;
    b->ptr=b->ref->buffer->data+b->ref->begin;
  }
}