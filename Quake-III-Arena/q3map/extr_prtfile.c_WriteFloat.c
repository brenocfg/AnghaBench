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
typedef  double vec_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ Q_rint (double) ; 
 double fabs (scalar_t__) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,double) ; 

void WriteFloat (FILE *f, vec_t v)
{
	if ( fabs(v - Q_rint(v)) < 0.001 )
		fprintf (f,"%i ",(int)Q_rint(v));
	else
		fprintf (f,"%f ",v);
}