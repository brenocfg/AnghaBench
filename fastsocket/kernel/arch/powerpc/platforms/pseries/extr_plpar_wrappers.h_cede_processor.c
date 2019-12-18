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
 int /*<<< orphan*/  H_CEDE ; 
 long plpar_hcall_norets (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline long cede_processor(void)
{
	return plpar_hcall_norets(H_CEDE);
}