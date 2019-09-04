#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_7__ {char* name; int flags; } ;
struct TYPE_6__ {scalar_t__ pix_fmt; int /*<<< orphan*/  fourcc; } ;
typedef  TYPE_1__ PixelFormatTag ;
typedef  TYPE_2__ AVPixFmtDescriptor ;

/* Variables and functions */
 int AV_PIX_FMT_FLAG_HWACCEL ; 
 scalar_t__ AV_PIX_FMT_NONE ; 
 char* av_fourcc2str (int /*<<< orphan*/ ) ; 
 int av_get_pix_fmt (char const*) ; 
 char* av_get_pix_fmt_name (scalar_t__) ; 
 TYPE_2__* av_pix_fmt_desc_get (int) ; 
 TYPE_1__* avpriv_get_raw_pix_fmt_tags () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 char getopt (int,char**,char*) ; 
 char* optarg ; 
 int /*<<< orphan*/  print_pix_fmt_fourccs (int,TYPE_1__ const*,char) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  usage () ; 

int main(int argc, char **argv)
{
    int i, list_fourcc_pix_fmt = 0, list_pix_fmt_fourccs = 0;
    const PixelFormatTag *pix_fmt_tags = avpriv_get_raw_pix_fmt_tags();
    const char *pix_fmt_name = NULL;
    char c;

    if (argc == 1) {
        usage();
        return 0;
    }

    while ((c = getopt(argc, argv, "hp:lL")) != -1) {
        switch (c) {
        case 'h':
            usage();
            return 0;
        case 'l':
            list_fourcc_pix_fmt = 1;
            break;
        case 'L':
            list_pix_fmt_fourccs = 1;
            break;
        case 'p':
            pix_fmt_name = optarg;
            break;
        case '?':
            usage();
            return 1;
        }
    }

    if (list_fourcc_pix_fmt)
        for (i = 0; pix_fmt_tags[i].pix_fmt != AV_PIX_FMT_NONE; i++)
            printf("%s: %s\n", av_fourcc2str(pix_fmt_tags[i].fourcc),
                   av_get_pix_fmt_name(pix_fmt_tags[i].pix_fmt));

    if (list_pix_fmt_fourccs) {
        for (i = 0; av_pix_fmt_desc_get(i); i++) {
            const AVPixFmtDescriptor *pix_desc = av_pix_fmt_desc_get(i);
            if (!pix_desc->name || pix_desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
                continue;
            printf("%s: ", pix_desc->name);
            print_pix_fmt_fourccs(i, pix_fmt_tags, ' ');
            printf("\n");
        }
    }

    if (pix_fmt_name) {
        enum AVPixelFormat pix_fmt = av_get_pix_fmt(pix_fmt_name);
        if (pix_fmt == AV_PIX_FMT_NONE) {
            fprintf(stderr, "Invalid pixel format selected '%s'\n", pix_fmt_name);
            return 1;
        }
        print_pix_fmt_fourccs(pix_fmt, pix_fmt_tags, '\n');
    }

    return 0;
}