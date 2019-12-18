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
struct TYPE_4__ {int /*<<< orphan*/  driver_data; TYPE_1__* poke; } ;
typedef  TYPE_2__ thread_video_t ;
struct video_shader {int dummy; } ;
struct TYPE_3__ {struct video_shader* (* get_current_shader ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 struct video_shader* stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct video_shader *thread_get_current_shader(void *data)
{
   thread_video_t *thr = (thread_video_t*)data;
   if (!thr || !thr->poke)
      return NULL;
   return thr->poke->get_current_shader(thr->driver_data);
}