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
struct ehca_shca {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ehca_process_eq (struct ehca_shca*,int) ; 

void ehca_tasklet_eq(unsigned long data)
{
	ehca_process_eq((struct ehca_shca*)data, 1);
}