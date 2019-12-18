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
#define  LINUX_LOGO_CLUT224 131 
#define  LINUX_LOGO_GRAY256 130 
#define  LINUX_LOGO_MONO 129 
#define  LINUX_LOGO_VGA16 128 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 char* filename ; 
 int getopt (int,char**,char*) ; 
 int logo_type ; 
 void* logoname ; 
 void* optarg ; 
 scalar_t__ opterr ; 
 int optind ; 
 void* outputname ; 
 char* programname ; 
 int /*<<< orphan*/  read_image () ; 
 int /*<<< orphan*/  strcmp (void*,char*) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  write_logo_clut224 () ; 
 int /*<<< orphan*/  write_logo_gray256 () ; 
 int /*<<< orphan*/  write_logo_mono () ; 
 int /*<<< orphan*/  write_logo_vga16 () ; 

int main(int argc, char *argv[])
{
    int opt;

    programname = argv[0];

    opterr = 0;
    while (1) {
	opt = getopt(argc, argv, "hn:o:t:");
	if (opt == -1)
	    break;

	switch (opt) {
	    case 'h':
		usage();
		break;

	    case 'n':
		logoname = optarg;
		break;

	    case 'o':
		outputname = optarg;
		break;

	    case 't':
		if (!strcmp(optarg, "mono"))
		    logo_type = LINUX_LOGO_MONO;
		else if (!strcmp(optarg, "vga16"))
		    logo_type = LINUX_LOGO_VGA16;
		else if (!strcmp(optarg, "clut224"))
		    logo_type = LINUX_LOGO_CLUT224;
		else if (!strcmp(optarg, "gray256"))
		    logo_type = LINUX_LOGO_GRAY256;
		else
		    usage();
		break;

	    default:
		usage();
		break;
	}
    }
    if (optind != argc-1)
	usage();

    filename = argv[optind];

    read_image();
    switch (logo_type) {
	case LINUX_LOGO_MONO:
	    write_logo_mono();
	    break;

	case LINUX_LOGO_VGA16:
	    write_logo_vga16();
	    break;

	case LINUX_LOGO_CLUT224:
	    write_logo_clut224();
	    break;

	case LINUX_LOGO_GRAY256:
	    write_logo_gray256();
	    break;
    }
    exit(0);
}