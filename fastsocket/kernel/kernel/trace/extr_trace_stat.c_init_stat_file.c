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
struct stat_session {int /*<<< orphan*/  file; TYPE_1__* ts; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  debugfs_create_file (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct stat_session*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stat_dir ; 
 int /*<<< orphan*/  tracing_stat_fops ; 
 scalar_t__ tracing_stat_init () ; 

__attribute__((used)) static int init_stat_file(struct stat_session *session)
{
	if (!stat_dir && tracing_stat_init())
		return -ENODEV;

	session->file = debugfs_create_file(session->ts->name, 0644,
					    stat_dir,
					    session, &tracing_stat_fops);
	if (!session->file)
		return -ENOMEM;
	return 0;
}