#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t buffer_size; } ;
typedef  TYPE_1__ rsound_t ;

/* Variables and functions */
 int /*<<< orphan*/  retro_assert (int /*<<< orphan*/ ) ; 
 int rsnd_get_ptr (TYPE_1__*) ; 

size_t rsd_get_avail(rsound_t *rd)
{
   retro_assert(rd != NULL);
   int ptr;
   ptr = rsnd_get_ptr(rd);
   return rd->buffer_size - ptr;
}