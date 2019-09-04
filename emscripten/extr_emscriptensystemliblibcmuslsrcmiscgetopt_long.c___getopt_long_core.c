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
struct option {char* name; int val; scalar_t__ has_arg; int* flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  __getopt_msg (char* const,char*,char* const,int /*<<< orphan*/ ) ; 
 int getopt (int,char* const*,char const*) ; 
 char* optarg ; 
 scalar_t__ opterr ; 
 size_t optind ; 
 int optopt ; 
 scalar_t__ required_argument ; 
 int /*<<< orphan*/  strlen (char* const) ; 

__attribute__((used)) static int __getopt_long_core(int argc, char *const *argv, const char *optstring, const struct option *longopts, int *idx, int longonly)
{
	optarg = 0;
	if (longopts && argv[optind][0] == '-' &&
		((longonly && argv[optind][1]) ||
		 (argv[optind][1] == '-' && argv[optind][2])))
	{
		int colon = optstring[optstring[0]=='+'||optstring[0]=='-']==':';
		int i, cnt, match;
		char *opt;
		for (cnt=i=0; longopts[i].name; i++) {
			const char *name = longopts[i].name;
			opt = argv[optind]+1;
			if (*opt == '-') opt++;
			for (; *name && *name == *opt; name++, opt++);
			if (*opt && *opt != '=') continue;
			match = i;
			if (!*name) {
				cnt = 1;
				break;
			}
			cnt++;
		}
		if (cnt==1) {
			i = match;
			optind++;
			optopt = longopts[i].val;
			if (*opt == '=') {
				if (!longopts[i].has_arg) {
					if (colon || !opterr)
						return '?';
					__getopt_msg(argv[0],
						": option does not take an argument: ",
						longopts[i].name,
						strlen(longopts[i].name));
					return '?';
				}
				optarg = opt+1;
			} else if (longopts[i].has_arg == required_argument) {
				if (!(optarg = argv[optind])) {
					if (colon) return ':';
					if (!opterr) return '?';
					__getopt_msg(argv[0],
						": option requires an argument: ",
						longopts[i].name,
						strlen(longopts[i].name));
					return '?';
				}
				optind++;
			}
			if (idx) *idx = i;
			if (longopts[i].flag) {
				*longopts[i].flag = longopts[i].val;
				return 0;
			}
			return longopts[i].val;
		}
		if (argv[optind][1] == '-') {
			if (!colon && opterr)
				__getopt_msg(argv[0], cnt ?
					": option is ambiguous: " :
					": unrecognized option: ",
					argv[optind]+2,
					strlen(argv[optind]+2));
			optind++;
			return '?';
		}
	}
	return getopt(argc, argv, optstring);
}