#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  BITMAP_FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * computed ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** object_sizes ; 

void
fini_object_sizes (void)
{
  int object_size_type;

  for (object_size_type = 0; object_size_type <= 3; object_size_type++)
    {
      free (object_sizes[object_size_type]);
      BITMAP_FREE (computed[object_size_type]);
      object_sizes[object_size_type] = NULL;
    }
}