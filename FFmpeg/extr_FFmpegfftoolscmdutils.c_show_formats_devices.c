#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* name; char* long_name; int /*<<< orphan*/  priv_class; } ;
struct TYPE_5__ {char* name; char* long_name; int /*<<< orphan*/  priv_class; } ;
typedef  TYPE_1__ AVOutputFormat ;
typedef  TYPE_2__ AVInputFormat ;

/* Variables and functions */
 int SHOW_DEMUXERS ; 
 int SHOW_MUXERS ; 
 TYPE_2__* av_demuxer_iterate (void**) ; 
 TYPE_1__* av_muxer_iterate (void**) ; 
 int is_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 scalar_t__ strcmp (char*,char const*) ; 

__attribute__((used)) static int show_formats_devices(void *optctx, const char *opt, const char *arg, int device_only, int muxdemuxers)
{
    void *ifmt_opaque = NULL;
    const AVInputFormat *ifmt  = NULL;
    void *ofmt_opaque = NULL;
    const AVOutputFormat *ofmt = NULL;
    const char *last_name;
    int is_dev;

    printf("%s\n"
           " D. = Demuxing supported\n"
           " .E = Muxing supported\n"
           " --\n", device_only ? "Devices:" : "File formats:");
    last_name = "000";
    for (;;) {
        int decode = 0;
        int encode = 0;
        const char *name      = NULL;
        const char *long_name = NULL;

        if (muxdemuxers !=SHOW_DEMUXERS) {
            ofmt_opaque = NULL;
            while ((ofmt = av_muxer_iterate(&ofmt_opaque))) {
                is_dev = is_device(ofmt->priv_class);
                if (!is_dev && device_only)
                    continue;
                if ((!name || strcmp(ofmt->name, name) < 0) &&
                    strcmp(ofmt->name, last_name) > 0) {
                    name      = ofmt->name;
                    long_name = ofmt->long_name;
                    encode    = 1;
                }
            }
        }
        if (muxdemuxers != SHOW_MUXERS) {
            ifmt_opaque = NULL;
            while ((ifmt = av_demuxer_iterate(&ifmt_opaque))) {
                is_dev = is_device(ifmt->priv_class);
                if (!is_dev && device_only)
                    continue;
                if ((!name || strcmp(ifmt->name, name) < 0) &&
                    strcmp(ifmt->name, last_name) > 0) {
                    name      = ifmt->name;
                    long_name = ifmt->long_name;
                    encode    = 0;
                }
                if (name && strcmp(ifmt->name, name) == 0)
                    decode = 1;
            }
        }
        if (!name)
            break;
        last_name = name;

        printf(" %s%s %-15s %s\n",
               decode ? "D" : " ",
               encode ? "E" : " ",
               name,
            long_name ? long_name:" ");
    }
    return 0;
}