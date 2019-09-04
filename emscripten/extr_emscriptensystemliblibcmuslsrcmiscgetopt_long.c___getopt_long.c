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
struct option {int dummy; } ;

/* Variables and functions */
 int __getopt_long_core (int,char* const*,char const*,struct option const*,int*,int) ; 
 scalar_t__ __optpos ; 
 scalar_t__ __optreset ; 
 int optind ; 
 int /*<<< orphan*/  permute (char* const*,int,int) ; 

__attribute__((used)) static int __getopt_long(int argc, char *const *argv, const char *optstring, const struct option *longopts, int *idx, int longonly)
{
	int ret, skipped, resumed;
	if (!optind || __optreset) {
		__optreset = 0;
		__optpos = 0;
		optind = 1;
	}
	if (optind >= argc || !argv[optind]) return -1;
	skipped = optind;
	if (optstring[0] != '+' && optstring[0] != '-') {
		int i;
		for (i=optind; ; i++) {
			if (i >= argc || !argv[i]) return -1;
			if (argv[i][0] == '-' && argv[i][1]) break;
		}
		optind = i;
	}
	resumed = optind;
	ret = __getopt_long_core(argc, argv, optstring, longopts, idx, longonly);
	if (resumed > skipped) {
		int i, cnt = optind-resumed;
		for (i=0; i<cnt; i++)
			permute(argv, skipped, optind-1);
		optind = skipped + cnt;
	}
	return ret;
}