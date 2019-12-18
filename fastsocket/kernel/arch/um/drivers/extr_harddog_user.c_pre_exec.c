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
struct dog_data {int /*<<< orphan*/ * close_me; int /*<<< orphan*/  stdout; int /*<<< orphan*/  stdin; } ;

/* Variables and functions */
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dup2 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void pre_exec(void *d)
{
	struct dog_data *data = d;

	dup2(data->stdin, 0);
	dup2(data->stdout, 1);
	dup2(data->stdout, 2);
	close(data->stdin);
	close(data->stdout);
	close(data->close_me[0]);
	close(data->close_me[1]);
}