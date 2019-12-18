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
struct TYPE_4__ {int io_count; TYPE_1__* io; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 TYPE_2__* video_layout_state ; 

int video_layout_io_find(const char *name)
{
   int i;

   for (i = 0; i < video_layout_state->io_count; ++i)
   {
      if (strcmp(video_layout_state->io[i].name, name) == 0)
         return i;
   }

   return -1;
}