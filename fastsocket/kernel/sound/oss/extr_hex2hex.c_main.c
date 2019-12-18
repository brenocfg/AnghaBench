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
 int* buf ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int loadhex (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdin ; 
 scalar_t__ strcmp (char const*,char*) ; 

int main( int argc, const char * argv [] )
{
	const char * varline;
	int i,l;
	int id=0;

	if(argv[1] && strcmp(argv[1], "-i")==0)
	{
		argv++;
		argc--;
		id=1;
	}
	if(argv[1]==NULL)
	{
		fprintf(stderr,"hex2hex: [-i] filename\n");
		exit(1);
	}
	varline = argv[1];
	l = loadhex(stdin, buf);

	printf("/*\n *\t Computer generated file. Do not edit.\n */\n");
        printf("static int %s_len = %d;\n", varline, l);
	printf("static unsigned char %s[] %s = {\n", varline, id?"__initdata":"");

	for (i=0;i<l;i++)
	{
		if (i) printf(",");
		if (i && !(i % 16)) printf("\n");
		printf("0x%02x", buf[i]);
	}

	printf("\n};\n\n");
	return 0;
}