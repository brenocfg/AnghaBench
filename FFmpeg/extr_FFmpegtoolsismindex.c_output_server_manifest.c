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
struct Tracks {int nb_tracks; struct Track** tracks; } ;
struct Track {int name; int track_id; int /*<<< orphan*/  bitrate; scalar_t__ is_video; } ;
typedef  int /*<<< orphan*/  filename ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char const*) ; 

__attribute__((used)) static void output_server_manifest(struct Tracks *tracks, const char *basename,
                                   const char *output_prefix,
                                   const char *path_prefix,
                                   const char *ismc_prefix)
{
    char filename[1000];
    FILE *out;
    int i;

    snprintf(filename, sizeof(filename), "%s%s.ism", output_prefix, basename);
    out = fopen(filename, "w");
    if (!out) {
        perror(filename);
        return;
    }
    fprintf(out, "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n");
    fprintf(out, "<smil xmlns=\"http://www.w3.org/2001/SMIL20/Language\">\n");
    fprintf(out, "\t<head>\n");
    fprintf(out, "\t\t<meta name=\"clientManifestRelativePath\" "
                 "content=\"%s%s.ismc\" />\n", ismc_prefix, basename);
    fprintf(out, "\t</head>\n");
    fprintf(out, "\t<body>\n");
    fprintf(out, "\t\t<switch>\n");
    for (i = 0; i < tracks->nb_tracks; i++) {
        struct Track *track = tracks->tracks[i];
        const char *type    = track->is_video ? "video" : "audio";
        fprintf(out, "\t\t\t<%s src=\"%s%s\" systemBitrate=\"%d\">\n",
                type, path_prefix, track->name, track->bitrate);
        fprintf(out, "\t\t\t\t<param name=\"trackID\" value=\"%d\" "
                     "valueType=\"data\" />\n", track->track_id);
        fprintf(out, "\t\t\t</%s>\n", type);
    }
    fprintf(out, "\t\t</switch>\n");
    fprintf(out, "\t</body>\n");
    fprintf(out, "</smil>\n");
    fclose(out);
}