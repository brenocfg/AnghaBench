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
struct raid6_recov_calls {char* name; int /*<<< orphan*/  datap; int /*<<< orphan*/  data2; int /*<<< orphan*/  (* valid ) () ;} ;
struct raid6_calls {int /*<<< orphan*/  (* gen_syndrome ) (int,int,void**) ;scalar_t__ (* valid ) () ;} ;

/* Variables and functions */
 int NDISKS ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/ * data ; 
 int /*<<< orphan*/  dataptrs ; 
 int /*<<< orphan*/  makedata () ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  raid6_2data_recov ; 
 struct raid6_calls** raid6_algos ; 
 struct raid6_calls raid6_call ; 
 int /*<<< orphan*/  raid6_datap_recov ; 
 struct raid6_recov_calls** raid6_recov_algos ; 
 int /*<<< orphan*/  raid6_select_algo () ; 
 int /*<<< orphan*/  stub1 () ; 
 scalar_t__ stub2 () ; 
 int /*<<< orphan*/  stub3 (int,int,void**) ; 
 scalar_t__ test_disks (int,int) ; 

int main(int argc, char *argv[])
{
	const struct raid6_calls *const *algo;
	const struct raid6_recov_calls *const *ra;
	int i, j;
	int err = 0;

	makedata();

	for (ra = raid6_recov_algos; *ra; ra++) {
		if ((*ra)->valid  && !(*ra)->valid())
			continue;
		raid6_2data_recov = (*ra)->data2;
		raid6_datap_recov = (*ra)->datap;

		printf("using recovery %s\n", (*ra)->name);

		for (algo = raid6_algos; *algo; algo++) {
			if (!(*algo)->valid || (*algo)->valid()) {
				raid6_call = **algo;

				/* Nuke syndromes */
				memset(data[NDISKS-2], 0xee, 2*PAGE_SIZE);

				/* Generate assumed good syndrome */
				raid6_call.gen_syndrome(NDISKS, PAGE_SIZE,
							(void **)&dataptrs);

				for (i = 0; i < NDISKS-1; i++)
					for (j = i+1; j < NDISKS; j++)
						err += test_disks(i, j);
			}
		}
		printf("\n");
	}

	printf("\n");
	/* Pick the best algorithm test */
	raid6_select_algo();

	if (err)
		printf("\n*** ERRORS FOUND ***\n");

	return err;
}