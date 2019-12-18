#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* name; int /*<<< orphan*/  type; int /*<<< orphan*/  blocks; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  Linux ; 
 int MAX_DEV_NAME ; 
 size_t MAX_PARTS ; 
 int /*<<< orphan*/  MsDos ; 
 int /*<<< orphan*/  Swap ; 
 int /*<<< orphan*/  atoi (char*) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int get_line (char*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ isspace (unsigned char) ; 
 int /*<<< orphan*/  num_linux ; 
 int /*<<< orphan*/  num_msdos ; 
 size_t num_partition ; 
 int /*<<< orphan*/  num_swap ; 
 TYPE_1__* partitions ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 scalar_t__ strstr (char*,char*) ; 
 int system (char*) ; 
 int /*<<< orphan*/  unlink (char*) ; 

__attribute__((used)) static void
read_partitions(void)
{
    FILE *f;
    char line[200];
    int length;
#ifndef DEBUG_THIS
    int ret = system("fdisk -l 2>/dev/null 1>/tmp/fdisk.output");
    if ((ret >> 8) != 0) {
	error("fdisk didn't run");
    }
    if ((f = fopen("/tmp/fdisk.output", "r")) == NULL)
#else
    if ((f = fopen("FDISK.TEST", "r")) == NULL)
#endif
	error("cannot read fdisk output");

    while (num_partition <= MAX_PARTS
	   && (length = get_line(line, 200, f)) >= 0) {
	if (strncmp(line, "/dev/", 5) == 0) {
	    int n = 0;
	    char *s = line + 5;
	    char *t = partitions[num_partition].name;
	    strcpy(t, "/dev/");
	    t += 5;
	    while (n < MAX_DEV_NAME && *s != '\0'
		   && !isspace((unsigned char) *s)) {
		*t++ = *s++;
		n++;
	    }
	    *t = '\0';
	    /* Read the size of the partition. */
	    t = line + 37;
	    while (isspace((unsigned char) *t))
		t++;
	    partitions[num_partition].blocks = atoi(t);
	    if (strstr(line, "Linux native")) {
		partitions[num_partition].type = Linux;
		num_partition++;
		num_linux++;
	    } else if (strstr(line, "Linux swap")) {
		partitions[num_partition].type = Swap;
		num_partition++;
		num_swap++;
	    } else if (strstr(line, "DOS")) {
		partitions[num_partition].type = MsDos;
		num_partition++;
		num_msdos++;
	    }
	}
    }
    fclose(f);
#ifndef DEBUG_THIS
    unlink("/tmp/fdisk.output");
#endif
}