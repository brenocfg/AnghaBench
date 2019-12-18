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
struct object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __register_frame_info_table (void*,struct object*) ; 
 struct object* malloc (int) ; 

void
__register_frame_table (void *begin)
{
  struct object *ob = malloc (sizeof (struct object));
  __register_frame_info_table (begin, ob);
}