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
struct TYPE_2__ {int /*<<< orphan*/  ptr_name; } ;
typedef  TYPE_1__ machopic_indirection ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,void const*) ; 

__attribute__((used)) static int
machopic_indirection_eq (const void *slot, const void *key)
{
  return strcmp (((const machopic_indirection *) slot)->ptr_name, key) == 0;
}