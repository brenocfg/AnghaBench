#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct TYPE_7__* next; } ;
typedef  TYPE_1__ ogg_reference ;

/* Variables and functions */
 TYPE_1__* ogg_buffer_walk (TYPE_1__*) ; 

__attribute__((used)) static ogg_reference *ogg_buffer_cat(ogg_reference *tail, ogg_reference *head){
  if(!tail)return head;

  while(tail->next){
    tail=tail->next;
  }
  tail->next=head;
  return ogg_buffer_walk(head);
}