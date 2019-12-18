#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t res_ptr; size_t tmpbuf_ptr; } ;
typedef  TYPE_1__ al_t ;

/* Variables and functions */
 size_t BUFSIZE ; 
 int /*<<< orphan*/  al_unqueue_buffers (TYPE_1__*) ; 

__attribute__((used)) static size_t al_write_avail(void *data)
{
   al_t *al = (al_t*)data;
   al_unqueue_buffers(al);
   return al->res_ptr * BUFSIZE + (BUFSIZE - al->tmpbuf_ptr);
}