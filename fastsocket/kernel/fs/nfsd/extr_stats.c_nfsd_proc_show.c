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
struct seq_file {int dummy; } ;
struct TYPE_2__ {unsigned int* th_usage; int ra_size; int* ra_depth; int* nfs4_opcount; int /*<<< orphan*/  th_fullcnt; int /*<<< orphan*/  th_cnt; int /*<<< orphan*/  io_write; int /*<<< orphan*/  io_read; int /*<<< orphan*/  fh_nocache_nondir; int /*<<< orphan*/  fh_nocache_dir; int /*<<< orphan*/  fh_anon; int /*<<< orphan*/  fh_lookup; int /*<<< orphan*/  fh_stale; int /*<<< orphan*/  rcnocache; int /*<<< orphan*/  rcmisses; int /*<<< orphan*/  rchits; } ;

/* Variables and functions */
 unsigned int HZ ; 
 int LAST_NFS4_OP ; 
 int /*<<< orphan*/  nfsd_svcstats ; 
 TYPE_1__ nfsdstats ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int,...) ; 
 int /*<<< orphan*/  seq_putc (struct seq_file*,char) ; 
 int /*<<< orphan*/  svc_seq_show (struct seq_file*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nfsd_proc_show(struct seq_file *seq, void *v)
{
	int i;

	seq_printf(seq, "rc %u %u %u\nfh %u %u %u %u %u\nio %u %u\n",
		      nfsdstats.rchits,
		      nfsdstats.rcmisses,
		      nfsdstats.rcnocache,
		      nfsdstats.fh_stale,
		      nfsdstats.fh_lookup,
		      nfsdstats.fh_anon,
		      nfsdstats.fh_nocache_dir,
		      nfsdstats.fh_nocache_nondir,
		      nfsdstats.io_read,
		      nfsdstats.io_write);
	/* thread usage: */
	seq_printf(seq, "th %u %u", nfsdstats.th_cnt, nfsdstats.th_fullcnt);
	for (i=0; i<10; i++) {
		unsigned int jifs = nfsdstats.th_usage[i];
		unsigned int sec = jifs / HZ, msec = (jifs % HZ)*1000/HZ;
		seq_printf(seq, " %u.%03u", sec, msec);
	}

	/* newline and ra-cache */
	seq_printf(seq, "\nra %u", nfsdstats.ra_size);
	for (i=0; i<11; i++)
		seq_printf(seq, " %u", nfsdstats.ra_depth[i]);
	seq_putc(seq, '\n');
	
	/* show my rpc info */
	svc_seq_show(seq, &nfsd_svcstats);

#ifdef CONFIG_NFSD_V4
	/* Show count for individual nfsv4 operations */
	/* Writing operation numbers 0 1 2 also for maintaining uniformity */
	seq_printf(seq,"proc4ops %u", LAST_NFS4_OP + 1);
	for (i = 0; i <= LAST_NFS4_OP; i++)
		seq_printf(seq, " %u", nfsdstats.nfs4_opcount[i]);

	seq_putc(seq, '\n');
#endif

	return 0;
}