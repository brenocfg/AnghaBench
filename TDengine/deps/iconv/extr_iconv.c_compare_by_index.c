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
struct nalias {scalar_t__ encoding_index; } ;

/* Variables and functions */

__attribute__((used)) static int compare_by_index (const void * arg1, const void * arg2)
{
  const struct nalias * alias1 = (const struct nalias *) arg1;
  const struct nalias * alias2 = (const struct nalias *) arg2;
  return (int)alias1->encoding_index - (int)alias2->encoding_index;
}