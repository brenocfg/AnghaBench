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
 int /*<<< orphan*/  base1 ; 
 int* ids1 ; 

__attribute__((used)) static int
get_ordinary_id (int x)
{
  if (ids1[x])
    return ids1[x];

  ids1[x] = base1++;
  return ids1[x];
}