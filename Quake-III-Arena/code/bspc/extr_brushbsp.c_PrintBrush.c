#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int numsides; TYPE_1__* sides; } ;
typedef  TYPE_2__ bspbrush_t ;
struct TYPE_4__ {int /*<<< orphan*/  winding; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  pw (int /*<<< orphan*/ ) ; 

void PrintBrush (bspbrush_t *brush)
{
	int		i;

	printf ("brush: %p\n", brush);
	for (i=0;i<brush->numsides ; i++)
	{
		pw(brush->sides[i].winding);
		printf ("\n");
	} //end for
}