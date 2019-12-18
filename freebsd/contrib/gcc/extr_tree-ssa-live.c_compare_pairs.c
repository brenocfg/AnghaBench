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
typedef  TYPE_1__* partition_pair_p ;
struct TYPE_2__ {int cost; } ;

/* Variables and functions */

__attribute__((used)) static
int compare_pairs (const void *p1, const void *p2)
{
  return (*(partition_pair_p *)p2)->cost - (*(partition_pair_p *)p1)->cost;
}