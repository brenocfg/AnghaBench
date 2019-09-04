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
 scalar_t__** atime ; 
 int /*<<< orphan*/  printf (char*,double,double,double,double,double,double) ; 

void print_time (int row)

{
printf("%11.5f%11.5f%11.5f%11.2f%11.4f%11.4f\n",   (double)atime[0][row],
       (double)atime[1][row], (double)atime[2][row], (double)atime[3][row], 
       (double)atime[4][row], (double)atime[5][row]);
       return;
}