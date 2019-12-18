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
 int /*<<< orphan*/  base2 ; 
 int* ids2 ; 

__attribute__((used)) static int
get_member_id (int x)
{
  if (ids2[x])
    return ids2[x];

  ids2[x] = base2++;
  return ids2[x];
}