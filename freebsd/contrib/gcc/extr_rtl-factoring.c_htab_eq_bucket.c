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
 scalar_t__ htab_hash_bucket (void const*) ; 

__attribute__((used)) static int
htab_eq_bucket (const void *p0, const void *p1)
{
  return htab_hash_bucket (p0) == htab_hash_bucket (p1);
}