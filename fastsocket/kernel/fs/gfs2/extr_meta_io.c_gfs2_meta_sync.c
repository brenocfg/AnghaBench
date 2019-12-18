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
struct gfs2_glock {int /*<<< orphan*/  gl_sbd; } ;
struct address_space {int dummy; } ;

/* Variables and functions */
 int filemap_fdatawait (struct address_space*) ; 
 int /*<<< orphan*/  filemap_fdatawrite (struct address_space*) ; 
 struct address_space* gfs2_glock2aspace (struct gfs2_glock*) ; 
 int /*<<< orphan*/  gfs2_io_error (int /*<<< orphan*/ ) ; 

void gfs2_meta_sync(struct gfs2_glock *gl)
{
	struct address_space *mapping = gfs2_glock2aspace(gl);
	int error;

	filemap_fdatawrite(mapping);
	error = filemap_fdatawait(mapping);

	if (error)
		gfs2_io_error(gl->gl_sbd);
}