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
struct file {struct file* sub_file; struct file* old_file; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG ; 
 int /*<<< orphan*/  DPRINTK (int /*<<< orphan*/ ,char*,struct file*) ; 
 int /*<<< orphan*/  __fsocket_filp_close (struct file*) ; 
 int /*<<< orphan*/  fd_reinstall (int,struct file*) ; 
 struct file* fget_light (int,int*) ; 
 int /*<<< orphan*/  fput_light (struct file*,int) ; 

__attribute__((used)) static void fsocket_filp_close_spawn(int fd)
{
	int fput_needed;
	struct file *nfile, *ofile, *sfile;

	nfile = fget_light(fd, &fput_needed);

	ofile = nfile->old_file;
	sfile = nfile->sub_file;

	fd_reinstall(fd, ofile);

	DPRINTK(DEBUG, "Close sub file 0x%p\n", sfile);
	__fsocket_filp_close(sfile);
	DPRINTK(DEBUG, "Close new file 0x%p\n", nfile);
	__fsocket_filp_close(nfile);

	fput_light(nfile, fput_needed);
}