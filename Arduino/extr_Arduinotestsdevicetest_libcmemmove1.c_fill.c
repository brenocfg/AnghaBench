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
 int MAX ; 

void
fill (unsigned char dest[MAX*3])
{
  size_t i;
  for (i = 0; i < MAX*3; i++)
    dest[i] = (10 + i) % MAX;
}