#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int daddr_t ;
typedef  int /*<<< orphan*/  buf ;
typedef  TYPE_1__* blist_t ;
struct TYPE_7__ {int bl_free; int bl_radix; } ;

/* Variables and functions */
 int blist_alloc (TYPE_1__*,int) ; 
 TYPE_1__* blist_create (int) ; 
 int /*<<< orphan*/  blist_free (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  blist_print (TYPE_1__*) ; 
 int /*<<< orphan*/  blist_resize (TYPE_1__**,int,int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  puts (char*) ; 
 int sscanf (char*,char*,int*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 
 int strtol (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
main(int ac, char **av)
{
	int size = 1024;
	int i;
	blist_t bl;

	for (i = 1; i < ac; ++i) {
		const char *ptr = av[i];
		if (*ptr != '-') {
			size = strtol(ptr, NULL, 0);
			continue;
		}
		ptr += 2;
		fprintf(stderr, "Bad option: %s\n", ptr - 2);
		exit(1);
	}
	bl = blist_create(size);
	blist_free(bl, 0, size);

	for (;;) {
		char buf[1024];
		daddr_t da = 0;
		daddr_t count = 0;


		printf("%d/%d/%d> ", bl->bl_free, size, bl->bl_radix);
		fflush(stdout);
		if (fgets(buf, sizeof(buf), stdin) == NULL)
			break;
		switch(buf[0]) {
		case 'r':
			if (sscanf(buf + 1, "%d", &count) == 1) {
				blist_resize(&bl, count, 1);
			} else {
				printf("?\n");
			}
		case 'p':
			blist_print(bl);
			break;
		case 'a':
			if (sscanf(buf + 1, "%d", &count) == 1) {
				daddr_t blk = blist_alloc(bl, count);
				printf("    R=%04x\n", blk);
			} else {
				printf("?\n");
			}
			break;
		case 'f':
			if (sscanf(buf + 1, "%x %d", &da, &count) == 2) {
				blist_free(bl, da, count);
			} else {
				printf("?\n");
			}
			break;
		case '?':
		case 'h':
			puts(
			    "p          -print\n"
			    "a %d       -allocate\n"
			    "f %x %d    -free\n"
			    "r %d       -resize\n"
			    "h/?        -help"
			);
			break;
		default:
			printf("?\n");
			break;
		}
	}
	return(0);
}