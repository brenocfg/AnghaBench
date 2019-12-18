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
struct TYPE_2__ {scalar_t__ write_idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  pc ; 
 TYPE_1__* tos ; 

__attribute__((used)) static void
remchar ()
{
  if (tos->write_idx)
    tos->write_idx--;
  pc++;
}