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
struct mibif {int dummy; } ;

/* Variables and functions */
 struct mibif* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mibif_list ; 

struct mibif *
mib_first_if(void)
{
	return (TAILQ_FIRST(&mibif_list));
}