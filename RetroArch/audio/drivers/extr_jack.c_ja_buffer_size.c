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
struct TYPE_2__ {size_t buffer_size; } ;
typedef  TYPE_1__ jack_t ;

/* Variables and functions */

__attribute__((used)) static size_t ja_buffer_size(void *data)
{
   jack_t *jd = (jack_t*)data;
   return jd->buffer_size;
}