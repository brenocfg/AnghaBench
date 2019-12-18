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
struct die_info {struct die_info* sibling; } ;

/* Variables and functions */

__attribute__((used)) static struct die_info *
sibling_die (struct die_info *die)
{
  return die->sibling;
}