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
struct option {int has_arg; int* flag; int val; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  longopts ;

/* Variables and functions */
 int BADCH ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 char* optarg ; 
 scalar_t__ opterr ; 
 int optind ; 
 int optopt ; 
 int /*<<< orphan*/  stderr ; 
 char* strchr (char const*,int) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int strlen (char*) ; 

int getopt_long(int argc, char * const argv[], const char *optstring,
struct option *longopts, int totlen) {
	static int lastidx,lastofs;
	char *tmp;
	int i,len;
	char param = 1;

again:
	if (optind >= argc || !argv[optind] || *argv[optind]!='-')
		return -1;

	if (argv[optind][0]=='-' && argv[optind][1]==0) {
		if(optind >= (argc - 1)){ /* no more input parameters */
			param = 0;
		}
		else{ /* more input parameters */
			if(argv[optind + 1][0] == '-'){
				param = 0; /* Missing parameter after '-' */
			}
			else{
				param = 2;
			}
		}
	}

	if (param == 0) {
		++optind;
		return (BADCH);
	}

	if (argv[optind][0]=='-') {	/* long option */
		char* arg=argv[optind]+1;
		const struct option* o;
		o=longopts;
		len=sizeof(longopts[0]);

		if (param > 1){
			arg = argv[optind+1];
			optind++;
		}
		else
			arg = argv[optind]+1;

		if(strlen(arg)>1){
			for (i=0;i<totlen;i=i+len,o++) {
				if (!strcmp(o->name,arg)) {	/* match */
					if (o->has_arg == 0) {
						if ((argv[optind+1])&&(!(argv[optind+1][0]=='-'))){
							fprintf(stderr,"%s: option does not require an argument. Ignoring %s\n",arg,argv[optind+1]);
							++optind;
						}
					}else{ 
						optarg=argv[optind+1];
						if(optarg){
							if (optarg[0] == '-'){ /* Has read next input parameter: No arg for current parameter */								
								if (opterr) {
									fprintf(stderr,"%s: option requires an argument\n",arg);
									return (BADCH);
								}
							}
						}
						if (!optarg && o->has_arg==1) {	/* no argument there */
							if (opterr) {
								fprintf(stderr,"%s: option requires an argument \n",arg);
								return (BADCH);
							}
						}
						++optind;
					}
					++optind;
					if (o->flag)
						*(o->flag)=o->val;
					else
						return o->val;
					return 0;
				}
			}//(end for)String not found in the list
			fprintf(stderr,"Invalid option %s\n",arg);
			++optind;
			return (BADCH);
		}else{ /*Single character input parameter*/
			if (*optstring==':') return ':';
			if (lastidx!=optind) {
				lastidx=optind; lastofs=0;
			}
			optopt=argv[optind][lastofs+1];
			if ((tmp=strchr(optstring,optopt))) {/*Found input parameter in list*/
				if (*tmp==0) {	/* apparently, we looked for \0, i.e. end of argument */
					++optind;
					goto again;
				}
				if (tmp[1]==':') {	/* argument expected */
					if (tmp[2]==':' || argv[optind][lastofs+2]) {	/* "-foo", return "oo" as optarg */
						if (!*(optarg=argv[optind]+lastofs+2)) optarg=0;
						goto found;
					}
					optarg=argv[optind+1];
					if(optarg){
						if (optarg[0] == '-'){ /* Has read next input parameter: No arg for current parameter */
							if (opterr) {
								fprintf(stderr,"%s: option requires an argument\n",arg);
								return (BADCH);
							}
						}
					}
					if (!optarg) {	/* missing argument */
						if (opterr) {
							fprintf(stderr,"%s: option requires an argument\n",arg);
							return (BADCH);
						}
					}
					++optind;
				}else {/*Argument not expected*/
					++lastofs;
					return optopt;
				}
found:
				++optind;
				return optopt;
			}	else {	/* not found */
				fprintf(stderr,"Invalid option %s\n",arg);
				++optind;
				return (BADCH);
			}//end of not found
		
		}// end of single character
	}//end '-'
	fprintf(stderr,"Invalid option\n");
	++optind;
	return (BADCH);;
}