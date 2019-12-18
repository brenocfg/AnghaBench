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
struct TYPE_3__ {int /*<<< orphan*/  base; struct TYPE_3__* next; } ;
typedef  TYPE_1__ _cpp_buff ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 

void
_cpp_free_buff (_cpp_buff *buff)
{
  _cpp_buff *next;

  for (; buff; buff = next)
    {
      next = buff->next;
      free (buff->base);
    }
}