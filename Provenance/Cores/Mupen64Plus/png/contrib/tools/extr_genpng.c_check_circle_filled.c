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
struct arg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FILTER_WIDTH ; 
 int circle_check_line (struct arg const*,double,double,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
check_circle_filled(const struct arg *arg, double x, double y)
{
   return circle_check_line(arg, x, y, FILTER_WIDTH);
}