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
struct TYPE_2__ {int num_buffers; } ;
typedef  TYPE_1__ al_t ;

/* Variables and functions */
 int BUFSIZE ; 

__attribute__((used)) static size_t al_buffer_size(void *data)
{
   al_t *al = (al_t*)data;
   return (al->num_buffers + 1) * BUFSIZE; /* Also got tmpbuf. */
}