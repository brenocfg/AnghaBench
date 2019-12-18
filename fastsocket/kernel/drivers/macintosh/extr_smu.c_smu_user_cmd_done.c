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
struct smu_private {int /*<<< orphan*/  wait; } ;
struct smu_cmd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void smu_user_cmd_done(struct smu_cmd *cmd, void *misc)
{
	struct smu_private *pp = misc;

	wake_up_all(&pp->wait);
}