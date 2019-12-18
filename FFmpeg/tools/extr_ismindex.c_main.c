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
struct Tracks {int video_track; int audio_track; int /*<<< orphan*/  nb_tracks; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  output_prefix_buf ;

/* Variables and functions */
 int /*<<< orphan*/  clean_tracks (struct Tracks*) ; 
 scalar_t__ handle_file (struct Tracks*,char*,int,int,char const*,char const*) ; 
 int /*<<< orphan*/  output_client_manifest (struct Tracks*,char const*,char const*,int) ; 
 int /*<<< orphan*/  output_server_manifest (struct Tracks*,char const*,char const*,char const*,char const*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int strlen (char const*) ; 
 int usage (char*,int) ; 

int main(int argc, char **argv)
{
    const char *basename = NULL;
    const char *path_prefix = "", *ismc_prefix = "";
    const char *output_prefix = "";
    char output_prefix_buf[2048];
    int split = 0, ismf = 0, i;
    struct Tracks tracks = { 0, .video_track = -1, .audio_track = -1 };

    for (i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-n")) {
            basename = argv[i + 1];
            i++;
        } else if (!strcmp(argv[i], "-path-prefix")) {
            path_prefix = argv[i + 1];
            i++;
        } else if (!strcmp(argv[i], "-ismc-prefix")) {
            ismc_prefix = argv[i + 1];
            i++;
        } else if (!strcmp(argv[i], "-output")) {
            output_prefix = argv[i + 1];
            i++;
            if (output_prefix[strlen(output_prefix) - 1] != '/') {
                snprintf(output_prefix_buf, sizeof(output_prefix_buf),
                         "%s/", output_prefix);
                output_prefix = output_prefix_buf;
            }
        } else if (!strcmp(argv[i], "-split")) {
            split = 1;
        } else if (!strcmp(argv[i], "-ismf")) {
            ismf = 1;
        } else if (argv[i][0] == '-') {
            return usage(argv[0], 1);
        } else {
            if (!basename)
                ismf = 0;
            if (handle_file(&tracks, argv[i], split, ismf,
                            basename, output_prefix))
                return 1;
        }
    }
    if (!tracks.nb_tracks || (!basename && !split))
        return usage(argv[0], 1);

    if (!split)
        output_server_manifest(&tracks, basename, output_prefix,
                               path_prefix, ismc_prefix);
    output_client_manifest(&tracks, basename, output_prefix, split);

    clean_tracks(&tracks);

    return 0;
}