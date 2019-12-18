#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  b; int /*<<< orphan*/  g; int /*<<< orphan*/  r; } ;
struct TYPE_5__ {int /*<<< orphan*/  b; int /*<<< orphan*/  g; int /*<<< orphan*/  r; } ;
typedef  TYPE_1__ COLOR ;

/* Variables and functions */
 int /*<<< orphan*/  gouraudTable () ; 
 double interpolate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_2__ leftColumnColor ; 

__attribute__((used)) static void gouraudLineSetup(double * redstep, double * greenstep, double * bluestep, int length, COLOR table1, COLOR table2) {

	gouraudTable();

	*redstep =interpolate(table1.r,table2.r,length);
	*greenstep =interpolate(table1.g,table2.g,length);
	*bluestep =interpolate(table1.b,table2.b,length);

	leftColumnColor.r = table1.r;
	leftColumnColor.g = table1.g;
	leftColumnColor.b = table1.b;
}