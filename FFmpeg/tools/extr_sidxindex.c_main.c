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
struct Tracks {int /*<<< orphan*/  nb_tracks; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  clean_tracks (struct Tracks*) ; 
 scalar_t__ handle_file (struct Tracks*,char*) ; 
 int /*<<< orphan*/  output_mpd (struct Tracks*,char const*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int usage (char*,int) ; 

int main(int argc, char **argv)
{
    const char *out = NULL;
    struct Tracks tracks = { 0 };
    int i;

    for (i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-out")) {
            out = argv[i + 1];
            i++;
        } else if (argv[i][0] == '-') {
            return usage(argv[0], 1);
        } else {
            if (handle_file(&tracks, argv[i]))
                return 1;
        }
    }
    if (!tracks.nb_tracks || !out)
        return usage(argv[0], 1);

    output_mpd(&tracks, out);

    clean_tracks(&tracks);

    return 0;
}