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
typedef  int /*<<< orphan*/ ** Hideset ;

/* Variables and functions */
 scalar_t__ domalloc (int) ; 
 int /*<<< orphan*/ *** hidesets ; 
 int maxhidesets ; 
 int /*<<< orphan*/  nhidesets ; 

void
iniths(void)
{
	hidesets = (Hideset *)domalloc(maxhidesets*sizeof(Hideset *));
	hidesets[0] = (Hideset)domalloc(sizeof(Hideset));
	*hidesets[0] = NULL;
	nhidesets++;
}