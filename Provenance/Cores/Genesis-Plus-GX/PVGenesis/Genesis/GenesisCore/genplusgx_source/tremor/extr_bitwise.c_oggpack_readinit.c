#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_3__* head; int /*<<< orphan*/  headend; scalar_t__ headptr; scalar_t__ count; TYPE_3__* tail; } ;
typedef  TYPE_2__ oggpack_buffer ;
struct TYPE_10__ {int /*<<< orphan*/  length; scalar_t__ begin; TYPE_1__* buffer; } ;
typedef  TYPE_3__ ogg_reference ;
struct TYPE_8__ {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  _span (TYPE_2__*) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

void oggpack_readinit(oggpack_buffer *b,ogg_reference *r){
  memset(b,0,sizeof(*b));

  b->tail=b->head=r;
  b->count=0;
  b->headptr=b->head->buffer->data+b->head->begin;
  b->headend=b->head->length;
  _span(b);
}