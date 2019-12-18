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
struct seq_file {int dummy; } ;
struct mddev {struct faulty_conf* private; } ;
struct faulty_conf {int /*<<< orphan*/  nfaults; int /*<<< orphan*/ * counters; int /*<<< orphan*/ * period; } ;

/* Variables and functions */
 size_t ReadFixable ; 
 size_t ReadPersistent ; 
 size_t ReadTransient ; 
 size_t WriteAll ; 
 size_t WritePersistent ; 
 size_t WriteTransient ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 

__attribute__((used)) static void status(struct seq_file *seq, struct mddev *mddev)
{
	struct faulty_conf *conf = mddev->private;
	int n;

	if ((n=atomic_read(&conf->counters[WriteTransient])) != 0)
		seq_printf(seq, " WriteTransient=%d(%d)",
			   n, conf->period[WriteTransient]);

	if ((n=atomic_read(&conf->counters[ReadTransient])) != 0)
		seq_printf(seq, " ReadTransient=%d(%d)",
			   n, conf->period[ReadTransient]);

	if ((n=atomic_read(&conf->counters[WritePersistent])) != 0)
		seq_printf(seq, " WritePersistent=%d(%d)",
			   n, conf->period[WritePersistent]);

	if ((n=atomic_read(&conf->counters[ReadPersistent])) != 0)
		seq_printf(seq, " ReadPersistent=%d(%d)",
			   n, conf->period[ReadPersistent]);


	if ((n=atomic_read(&conf->counters[ReadFixable])) != 0)
		seq_printf(seq, " ReadFixable=%d(%d)",
			   n, conf->period[ReadFixable]);

	if ((n=atomic_read(&conf->counters[WriteAll])) != 0)
		seq_printf(seq, " WriteAll");

	seq_printf(seq, " nfaults=%d", conf->nfaults);
}