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
struct TYPE_3__ {scalar_t__ elements_count; int /*<<< orphan*/ * elements; int /*<<< orphan*/  blend; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ layer_t ;

/* Variables and functions */
 int /*<<< orphan*/  VIDEO_LAYOUT_BLEND_ALPHA ; 
 int /*<<< orphan*/  init_string (char const*) ; 

void layer_init(layer_t *layer, const char *name)
{
   layer->name = init_string(name);
   layer->blend = VIDEO_LAYOUT_BLEND_ALPHA;
   layer->elements = NULL;
   layer->elements_count = 0;
}