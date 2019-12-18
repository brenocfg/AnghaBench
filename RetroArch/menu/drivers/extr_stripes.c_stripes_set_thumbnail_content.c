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
struct TYPE_2__ {int /*<<< orphan*/  thumbnail_content; } ;
typedef  TYPE_1__ stripes_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strdup (char*) ; 
 int /*<<< orphan*/  string_is_empty (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stripes_set_thumbnail_content(void *data, char *s, size_t len)
{
   stripes_handle_t *stripes = (stripes_handle_t*)data;
   if (!stripes)
      return;
   if (!string_is_empty(stripes->thumbnail_content))
      free(stripes->thumbnail_content);
   stripes->thumbnail_content = strdup(s);
}