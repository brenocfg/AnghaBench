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
struct TYPE_3__ {int value; struct TYPE_3__* next; } ;
typedef  TYPE_1__ worker_args ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,int,TYPE_1__*) ; 

int main() {
  worker_args a;
  worker_args b;
  a.value = 60;
  a.next = &b;
  b.value = 900;
  b.next = NULL;
  worker_args* c = &a;
  int total = 0;
  while (c) {
    total += c->value;
    c = c->next;
  }

  // Chunk of em
  worker_args chunk[10];
  for (int i = 0; i < 9; i++) {
    chunk[i].value = i * 10;
    chunk[i].next = &chunk[i + 1];
  }
  chunk[9].value = 90;
  chunk[9].next = &chunk[0];

  c = chunk;
  do {
    total += c->value;
    c = c->next;
  } while (c != chunk);

  printf("*%d,%p*\n", total, b.next);
  // NULL *is* 0, in C/C++. No JS null! (null == 0 is false, etc.)

  return 0;
}