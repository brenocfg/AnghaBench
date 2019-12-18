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
struct scsi_cmnd {unsigned long serial_number; int /*<<< orphan*/  request; } ;
struct mscp {int /*<<< orphan*/  din; struct scsi_cmnd* SCpnt; } ;
struct hostdata {struct mscp* cp; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INFO ; 
 unsigned long ULONG_MAX ; 
 int /*<<< orphan*/  YESNO (unsigned int) ; 
 unsigned long blk_rq_pos (int /*<<< orphan*/ ) ; 
 unsigned long blk_rq_sectors (int /*<<< orphan*/ ) ; 
 unsigned int link_statistics ; 
 int /*<<< orphan*/  printk (char*,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  scmd_printk (int /*<<< orphan*/ ,struct scsi_cmnd*,char*,char*,unsigned long,unsigned int,unsigned int,unsigned int,unsigned long,unsigned long,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sort (unsigned long*,unsigned int*,unsigned int,unsigned int) ; 

__attribute__((used)) static int reorder(struct hostdata *ha, unsigned long cursec,
		   unsigned int ihdlr, unsigned int il[], unsigned int n_ready)
{
	struct scsi_cmnd *SCpnt;
	struct mscp *cpp;
	unsigned int k, n;
	unsigned int rev = 0, s = 1, r = 1;
	unsigned int input_only = 1, overlap = 0;
	unsigned long sl[n_ready], pl[n_ready], ll[n_ready];
	unsigned long maxsec = 0, minsec = ULONG_MAX, seek = 0, iseek = 0;
	unsigned long ioseek = 0;

	static unsigned int flushcount = 0, batchcount = 0, sortcount = 0;
	static unsigned int readycount = 0, ovlcount = 0, inputcount = 0;
	static unsigned int readysorted = 0, revcount = 0;
	static unsigned long seeksorted = 0, seeknosort = 0;

	if (link_statistics && !(++flushcount % link_statistics))
		printk("fc %d bc %d ic %d oc %d rc %d rs %d sc %d re %d"
		       " av %ldK as %ldK.\n", flushcount, batchcount,
		       inputcount, ovlcount, readycount, readysorted, sortcount,
		       revcount, seeknosort / (readycount + 1),
		       seeksorted / (readycount + 1));

	if (n_ready <= 1)
		return 0;

	for (n = 0; n < n_ready; n++) {
		k = il[n];
		cpp = &ha->cp[k];
		SCpnt = cpp->SCpnt;

		if (!cpp->din)
			input_only = 0;

		if (blk_rq_pos(SCpnt->request) < minsec)
			minsec = blk_rq_pos(SCpnt->request);
		if (blk_rq_pos(SCpnt->request) > maxsec)
			maxsec = blk_rq_pos(SCpnt->request);

		sl[n] = blk_rq_pos(SCpnt->request);
		ioseek += blk_rq_sectors(SCpnt->request);

		if (!n)
			continue;

		if (sl[n] < sl[n - 1])
			s = 0;
		if (sl[n] > sl[n - 1])
			r = 0;

		if (link_statistics) {
			if (sl[n] > sl[n - 1])
				seek += sl[n] - sl[n - 1];
			else
				seek += sl[n - 1] - sl[n];
		}

	}

	if (link_statistics) {
		if (cursec > sl[0])
			seek += cursec - sl[0];
		else
			seek += sl[0] - cursec;
	}

	if (cursec > ((maxsec + minsec) / 2))
		rev = 1;

	if (ioseek > ((maxsec - minsec) / 2))
		rev = 0;

	if (!((rev && r) || (!rev && s)))
		sort(sl, il, n_ready, rev);

	if (!input_only)
		for (n = 0; n < n_ready; n++) {
			k = il[n];
			cpp = &ha->cp[k];
			SCpnt = cpp->SCpnt;
			ll[n] = blk_rq_sectors(SCpnt->request);
			pl[n] = SCpnt->serial_number;

			if (!n)
				continue;

			if ((sl[n] == sl[n - 1])
			    || (!rev && ((sl[n - 1] + ll[n - 1]) > sl[n]))
			    || (rev && ((sl[n] + ll[n]) > sl[n - 1])))
				overlap = 1;
		}

	if (overlap)
		sort(pl, il, n_ready, 0);

	if (link_statistics) {
		if (cursec > sl[0])
			iseek = cursec - sl[0];
		else
			iseek = sl[0] - cursec;
		batchcount++;
		readycount += n_ready;
		seeknosort += seek / 1024;
		if (input_only)
			inputcount++;
		if (overlap) {
			ovlcount++;
			seeksorted += iseek / 1024;
		} else
			seeksorted += (iseek + maxsec - minsec) / 1024;
		if (rev && !r) {
			revcount++;
			readysorted += n_ready;
		}
		if (!rev && !s) {
			sortcount++;
			readysorted += n_ready;
		}
	}
#if defined(DEBUG_LINKED_COMMANDS)
	if (link_statistics && (overlap || !(flushcount % link_statistics)))
		for (n = 0; n < n_ready; n++) {
			k = il[n];
			cpp = &ha->cp[k];
			SCpnt = cpp->SCpnt;
			scmd_printk(KERN_INFO, SCpnt,
			    "%s pid %ld mb %d fc %d nr %d sec %ld ns %u"
			     " cur %ld s:%c r:%c rev:%c in:%c ov:%c xd %d.\n",
			     (ihdlr ? "ihdlr" : "qcomm"),
			     SCpnt->serial_number, k, flushcount,
			     n_ready, blk_rq_pos(SCpnt->request),
			     blk_rq_sectors(SCpnt->request), cursec, YESNO(s),
			     YESNO(r), YESNO(rev), YESNO(input_only),
			     YESNO(overlap), cpp->din);
		}
#endif
	return overlap;
}