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
struct bench_suite {char* name; int /*<<< orphan*/  (* fn ) (int,char const**,int /*<<< orphan*/ *) ;} ;
struct bench_subsys {char* name; struct bench_suite* suites; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stub1 (int,char const**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void all_suite(struct bench_subsys *subsys)	  /* FROM HERE */
{
	int i;
	const char *argv[2];
	struct bench_suite *suites = subsys->suites;

	argv[1] = NULL;
	/*
	 * TODO:
	 * preparing preset parameters for
	 * embedded, ordinary PC, HPC, etc...
	 * will be helpful
	 */
	for (i = 0; suites[i].fn; i++) {
		printf("# Running %s/%s benchmark...\n",
		       subsys->name,
		       suites[i].name);

		argv[1] = suites[i].name;
		suites[i].fn(1, argv, NULL);
		printf("\n");
	}
}