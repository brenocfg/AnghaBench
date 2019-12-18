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
struct ipoib_path_iter {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  sl; scalar_t__ dlid; int /*<<< orphan*/  rate; int /*<<< orphan*/  dgid; } ;
struct ipoib_path {TYPE_1__ pathrec; } ;

/* Variables and functions */
 int /*<<< orphan*/  be16_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  format_gid (int /*<<< orphan*/ *,char*) ; 
 int ib_rate_to_mbps (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipoib_path_iter_read (struct ipoib_path_iter*,struct ipoib_path*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char*,char*,...) ; 
 int /*<<< orphan*/  seq_putc (struct seq_file*,char) ; 

__attribute__((used)) static int ipoib_path_seq_show(struct seq_file *file, void *iter_ptr)
{
	struct ipoib_path_iter *iter = iter_ptr;
	char gid_buf[sizeof "ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff"];
	struct ipoib_path path;
	int rate;

	if (!iter)
		return 0;

	ipoib_path_iter_read(iter, &path);

	format_gid(&path.pathrec.dgid, gid_buf);

	seq_printf(file,
		   "GID: %s\n"
		   "  complete: %6s\n",
		   gid_buf, path.pathrec.dlid ? "yes" : "no");

	if (path.pathrec.dlid) {
		rate = ib_rate_to_mbps(path.pathrec.rate);

		seq_printf(file,
			   "  DLID:     0x%04x\n"
			   "  SL: %12d\n"
			   "  rate: %8d.%d Gb/sec\n",
			   be16_to_cpu(path.pathrec.dlid),
			   path.pathrec.sl,
			   rate / 1000, rate % 1000);
	}

	seq_putc(file, '\n');

	return 0;
}