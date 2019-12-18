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
struct capi20_appl {int /*<<< orphan*/  nsentdatapkt; int /*<<< orphan*/  nsentctlpkt; int /*<<< orphan*/  nrecvdatapkt; int /*<<< orphan*/  nrecvctlpkt; int /*<<< orphan*/  applid; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
applstats_show(struct seq_file *seq, void *v)
{
	struct capi20_appl *ap = *(struct capi20_appl **) v;

	if (!ap)
		return 0;

	seq_printf(seq, "%u %lu %lu %lu %lu\n",
		   ap->applid,
		   ap->nrecvctlpkt,
		   ap->nrecvdatapkt,
		   ap->nsentctlpkt,
		   ap->nsentdatapkt);

	return 0;
}