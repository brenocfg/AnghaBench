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
typedef  int /*<<< orphan*/  conversion ;

/* Variables and functions */
 scalar_t__ conversion_obstack_alloc (size_t) ; 

__attribute__((used)) static conversion **
alloc_conversions (size_t n)
{
  return (conversion **) conversion_obstack_alloc (n * sizeof (conversion *));
}