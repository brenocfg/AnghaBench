#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  io_t ;
struct TYPE_4__ {int io_count; TYPE_1__* io; } ;
struct TYPE_3__ {int base_value; int value; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_string (char const*) ; 
 int /*<<< orphan*/  vec_size (void**,int,int) ; 
 TYPE_2__* video_layout_state ; 

int video_layout_io_assign(const char *name, int base_value)
{
   int index;

   index = video_layout_state->io_count;

   vec_size((void**)&video_layout_state->io, sizeof(io_t), ++video_layout_state->io_count);

   video_layout_state->io[index].name       = init_string(name);
   video_layout_state->io[index].base_value = base_value;
   video_layout_state->io[index].value      = base_value;

   return index;
}