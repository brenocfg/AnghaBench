#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* buffer; } ;
struct TYPE_5__ {TYPE_1__ atlas; } ;
typedef  TYPE_2__ stb_font_renderer_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 

__attribute__((used)) static void font_renderer_stb_free(void *data)
{
   stb_font_renderer_t *self = (stb_font_renderer_t*)data;

   free(self->atlas.buffer);
   free(self);
}