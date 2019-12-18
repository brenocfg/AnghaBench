#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct c_binding {struct c_binding* prev; } ;

/* Variables and functions */
 struct c_binding* binding_freelist ; 
 int /*<<< orphan*/  memset (struct c_binding*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct c_binding *
free_binding_and_advance (struct c_binding *b)
{
  struct c_binding *prev = b->prev;

  memset (b, 0, sizeof (struct c_binding));
  b->prev = binding_freelist;
  binding_freelist = b;

  return prev;
}