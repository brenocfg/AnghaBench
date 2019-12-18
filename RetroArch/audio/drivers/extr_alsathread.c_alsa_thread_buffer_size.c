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
typedef  TYPE_1__ alsa_thread_t ;

/* Variables and functions */

__attribute__((used)) static size_t alsa_thread_buffer_size(void *data)
{
   alsa_thread_t *alsa = (alsa_thread_t*)data;
   return alsa->buffer_size;
}