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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int,int,int,int,int) ; 
 TYPE_1__ sharpsl_pm ; 

__attribute__((used)) static int get_select_val(int *val)
{
	int i, j, k, temp, sum = 0;

	/* Find MAX val */
	temp = val[0];
	j=0;
	for (i=1; i<5; i++) {
		if (temp < val[i]) {
			temp = val[i];
			j = i;
		}
	}

	/* Find MIN val */
	temp = val[4];
	k=4;
	for (i=3; i>=0; i--) {
		if (temp > val[i]) {
			temp = val[i];
			k = i;
		}
	}

	for (i=0; i<5; i++)
		if (i != j && i != k )
			sum += val[i];

	dev_dbg(sharpsl_pm.dev, "Average: %d from values: %d, %d, %d, %d, %d\n", sum/3, val[0], val[1], val[2], val[3], val[4]);

	return (sum/3);
}