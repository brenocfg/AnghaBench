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
typedef  int /*<<< orphan*/  tdata_t ;

/* Variables and functions */
 int CTF_COMPRESS ; 
 int CTF_SWAP_BYTES ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mktmpname (char*,char*) ; 
 scalar_t__ read_ctf (char**,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  read_ctf_save_cb ; 
 scalar_t__ rename (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tdata_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  terminate (char*,char*,...) ; 
 int /*<<< orphan*/  tmpname ; 
 int /*<<< orphan*/  write_ctf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
copy_ctf_data(char *srcfile, char *destfile, int keep_stabs)
{
	tdata_t *srctd;

	if (read_ctf(&srcfile, 1, NULL, read_ctf_save_cb, &srctd, 1) == 0)
		terminate("No CTF data found in source file %s\n", srcfile);

	tmpname = mktmpname(destfile, ".ctf");
	write_ctf(srctd, destfile, tmpname, CTF_COMPRESS | CTF_SWAP_BYTES | keep_stabs);
	if (rename(tmpname, destfile) != 0) {
		terminate("Couldn't rename temp file %s to %s", tmpname,
		    destfile);
	}
	free(tmpname);
	tdata_free(srctd);
}