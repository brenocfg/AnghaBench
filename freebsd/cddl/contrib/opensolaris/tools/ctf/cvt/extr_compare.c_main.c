#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  td_iihash; } ;
typedef  TYPE_1__ tdata_t ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int hash_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash_iter (int /*<<< orphan*/ ,int (*) (),int /*<<< orphan*/ *) ; 
 scalar_t__ iidesc_dump ; 
 int /*<<< orphan*/  merge_into_master (TYPE_1__*,TYPE_1__*,TYPE_1__*,int) ; 
 char* progname ; 
 scalar_t__ read_ctf (char**,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_ctf_save_cb ; 
 scalar_t__ read_stabs (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* tdata_new () ; 
 int /*<<< orphan*/  terminate (char*,char*,...) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char **argv)
{
	tdata_t *ctftd, *stabrtd, *stabtd, *difftd;
	char *ctfname, *stabname;
	int new;

	progname = argv[0];

	if (argc != 3) {
		usage();
		exit(2);
	}

	ctfname = argv[1];
	stabname = argv[2];

	stabrtd = tdata_new();
	stabtd = tdata_new();
	difftd = tdata_new();

	if (read_stabs(stabrtd, stabname, 0) != 0)
		merge_into_master(stabrtd, stabtd, NULL, 1);
	else if (read_ctf(&stabname, 1, NULL, read_ctf_save_cb, &stabtd, 0)
	    == 0)
		terminate("%s doesn't have stabs or CTF\n", stabname);

	if (read_ctf(&ctfname, 1, NULL, read_ctf_save_cb, &ctftd, 0) == 0)
		terminate("%s doesn't contain CTF data\n", ctfname);

	merge_into_master(stabtd, ctftd, difftd, 0);

	if ((new = hash_count(difftd->td_iihash)) != 0) {
		(void) hash_iter(difftd->td_iihash, (int (*)())iidesc_dump,
		    NULL);
		terminate("%s grew by %d\n", stabname, new);
	}

	return (0);
}