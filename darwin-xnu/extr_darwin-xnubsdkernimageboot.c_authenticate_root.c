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

/* Variables and functions */
 int /*<<< orphan*/  AUTHDBG (char*,...) ; 
 int /*<<< orphan*/  AUTHPRNT (char*,...) ; 
 int construct_chunklist_path (char const*,char**) ; 
 int /*<<< orphan*/  kfree_safe (char*) ; 
 int read_file (char*,void**,size_t*) ; 
 int validate_chunklist (void*,size_t) ; 
 int validate_root_image (char const*,void*) ; 

__attribute__((used)) static int
authenticate_root(const char *root_path)
{
	char *chunklist_path = NULL;
	void *chunklist_buf = NULL;
	size_t chunklist_len = 32*1024*1024UL;
	int err = 0;

	err = construct_chunklist_path(root_path, &chunklist_path);
	if (err) {
		AUTHPRNT("failed creating chunklist path");
		goto out;
	}

	AUTHDBG("validating root against chunklist %s", chunklist_path);

	/*
	 * Read and authenticate the chunklist, then validate the root image against
	 * the chunklist.
	 */

	AUTHDBG("reading chunklist");
	err = read_file(chunklist_path, &chunklist_buf, &chunklist_len);
	if (err) {
		AUTHPRNT("failed to read chunklist");
		goto out;
	}

	AUTHDBG("validating chunklist");
	err = validate_chunklist(chunklist_buf, chunklist_len);
	if (err < 0) {
		AUTHDBG("missing or incorrect signature on chunklist");
		goto out;
	} else if (err) {
		AUTHPRNT("failed to validate chunklist");
		goto out;
	} else {
		AUTHDBG("successfully validated chunklist");
	}

	AUTHDBG("validating root image against chunklist");
	err = validate_root_image(root_path, chunklist_buf);
	if (err) {
		AUTHPRNT("failed to validate root image against chunklist (%d)", err);
		goto out;
	}

	/* everything checked out - go ahead and mount this */
	AUTHDBG("root image authenticated");

 out:
	kfree_safe(chunklist_buf);
	kfree_safe(chunklist_path);
	return err;
}