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
struct vacm_access {int dummy; } ;

/* Variables and functions */
 struct vacm_access* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vacm_accesslist ; 

struct vacm_access *
vacm_first_access_rule(void)
{
	return (TAILQ_FIRST(&vacm_accesslist));
}