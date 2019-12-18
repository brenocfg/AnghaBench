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
 int square_check_line (struct arg const*,double,double,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
check_square_filled(const struct arg *arg, double x, double y)
{
   /* The filter extends +/-FILTER_WIDTH each side of each output point, so
    * the check has to expand and contract the square by that amount; '0'
    * means close enough to the edge of the square that the bicubic filter has
    * to be run, OUTSIDE means alpha==0, INSIDE means alpha==1.
    */
   return square_check_line(arg, x, y, FILTER_WIDTH);
}