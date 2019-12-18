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
struct TYPE_3__ {int is_valid; char* path; int /*<<< orphan*/ * data; scalar_t__ height; scalar_t__ width; scalar_t__ max_height; scalar_t__ max_width; } ;
typedef  TYPE_1__ thumbnail_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rgui_thumbnail_free(thumbnail_t *thumbnail)
{
   if (!thumbnail)
      return;
   
   thumbnail->max_width = 0;
   thumbnail->max_height = 0;
   thumbnail->width = 0;
   thumbnail->height = 0;
   thumbnail->is_valid = false;
   thumbnail->path[0] = '\0';
   
   if (thumbnail->data)
      free(thumbnail->data);
   thumbnail->data = NULL;
}