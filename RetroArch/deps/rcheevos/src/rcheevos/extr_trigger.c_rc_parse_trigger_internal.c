#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* requirement; TYPE_4__* alternative; } ;
typedef  TYPE_2__ rc_trigger_t ;
struct TYPE_10__ {scalar_t__ offset; } ;
typedef  TYPE_3__ rc_parse_state_t ;
struct TYPE_11__ {struct TYPE_11__* next; } ;
typedef  TYPE_4__ rc_condset_t ;
struct TYPE_8__ {scalar_t__ next; } ;

/* Variables and functions */
 void* rc_parse_condset (char const**,TYPE_3__*) ; 

void rc_parse_trigger_internal(rc_trigger_t* self, const char** memaddr, rc_parse_state_t* parse) {
  rc_condset_t** next;
  const char* aux;

  aux = *memaddr;
  next = &self->alternative;

  if (*aux == 's' || *aux == 'S') {
    self->requirement = 0;
  }
  else {
    self->requirement = rc_parse_condset(&aux, parse);

    if (parse->offset < 0) {
      return;
    }

    self->requirement->next = 0;
  }

  while (*aux == 's' || *aux == 'S') {
    aux++;
    *next = rc_parse_condset(&aux, parse);

    if (parse->offset < 0) {
      return;
    }

    next = &(*next)->next;
  }
  
  *next = 0;
  *memaddr = aux;
}