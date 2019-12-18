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
struct file {int f_flags; int /*<<< orphan*/  f_path; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENFILE ; 
 struct file* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FMODE_READ ; 
 int O_NONBLOCK ; 
 int O_RDONLY ; 
 struct file* alloc_file (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  path_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_pipefifo_fops ; 

struct file *create_read_pipe(struct file *wrf, int flags)
{
	/* Grab pipe from the writer */
	struct file *f = alloc_file(&wrf->f_path, FMODE_READ,
				    &read_pipefifo_fops);
	if (!f)
		return ERR_PTR(-ENFILE);

	path_get(&wrf->f_path);
	f->f_flags = O_RDONLY | (flags & O_NONBLOCK);

	return f;
}