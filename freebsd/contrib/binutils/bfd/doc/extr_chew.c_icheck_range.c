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
 scalar_t__ STACK ; 
 int /*<<< orphan*/  die (char*) ; 
 scalar_t__ isp ; 
 scalar_t__ istack ; 

__attribute__((used)) static void
icheck_range ()
{
  if (isp < istack)
    die ("underflow in integer stack");
  if (isp >= istack + STACK)
    die ("overflow in integer stack");
}