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
typedef  int double_t ;

/* Variables and functions */
 int erx ; 
 int fabs (double) ; 
 int pa0 ; 
 int pa1 ; 
 int pa2 ; 
 int pa3 ; 
 int pa4 ; 
 int pa5 ; 
 int pa6 ; 
 int qa1 ; 
 int qa2 ; 
 int qa3 ; 
 int qa4 ; 
 int qa5 ; 
 int qa6 ; 

__attribute__((used)) static double erfc1(double x)
{
	double_t s,P,Q;

	s = fabs(x) - 1;
	P = pa0+s*(pa1+s*(pa2+s*(pa3+s*(pa4+s*(pa5+s*pa6)))));
	Q = 1+s*(qa1+s*(qa2+s*(qa3+s*(qa4+s*(qa5+s*qa6)))));
	return 1 - erx - P/Q;
}