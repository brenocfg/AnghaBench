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
struct inf {int dummy; } ;

/* Variables and functions */
 struct inf* current_inferior ; 
 struct inf* make_inf () ; 

__attribute__((used)) static struct inf *
cur_inf (void)
{
  if (!current_inferior)
    current_inferior = make_inf ();
  return current_inferior;
}