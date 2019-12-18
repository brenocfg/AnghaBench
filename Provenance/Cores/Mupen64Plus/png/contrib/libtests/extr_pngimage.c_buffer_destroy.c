#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct buffer_list {int dummy; } ;
struct TYPE_2__ {struct buffer_list* next; } ;
struct buffer {TYPE_1__ first; } ;

/* Variables and functions */
 int /*<<< orphan*/  buffer_destroy_list (struct buffer_list*) ; 
 int /*<<< orphan*/  buffer_init (struct buffer*) ; 

__attribute__((used)) static void
buffer_destroy(struct buffer *buffer)
{
   struct buffer_list *list = buffer->first.next;
   buffer_init(buffer);
   buffer_destroy_list(list);
}