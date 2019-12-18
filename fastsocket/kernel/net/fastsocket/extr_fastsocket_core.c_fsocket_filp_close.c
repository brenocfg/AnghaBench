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
struct file {struct file* old_file; struct file* sub_file; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG ; 
 int /*<<< orphan*/  DPRINTK (int /*<<< orphan*/ ,char*,struct file*) ; 
 int __fsocket_filp_close (struct file*) ; 

__attribute__((used)) static inline int fsocket_filp_close(struct file *file)
{
	struct file *sfile, *ofile;
	int retval;

	sfile = file->sub_file;
	ofile = file->old_file;

	DPRINTK(DEBUG, "Close file 0x%p\n", file);

	retval = __fsocket_filp_close(file);

	//FIXME: To close sub file and old file after close file successfully? Or the other way around.

	if (sfile && !retval) {
		DPRINTK(DEBUG, "Close sub file 0x%p\n", sfile);
		__fsocket_filp_close(sfile);
	}

	//Close old file when we don't need the socket fd, so it's safe to install the ofile back when spawn failed
	if (ofile && !retval) {
		DPRINTK(DEBUG, "Close old file 0x%p\n", ofile);
		__fsocket_filp_close(ofile);
	}

	return 0;
}