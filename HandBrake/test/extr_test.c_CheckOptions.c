#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  short_name; } ;
typedef  TYPE_1__ hb_container_t ;

/* Variables and functions */
 int /*<<< orphan*/ * atracks ; 
 int audio_all ; 
 int /*<<< orphan*/ * audio_lang_list ; 
 int count_subtitles (int /*<<< orphan*/ ) ; 
 scalar_t__ display_width ; 
 int /*<<< orphan*/ * format ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  hb_container_get_from_extension (char const*) ; 
 TYPE_1__* hb_container_get_from_format (int /*<<< orphan*/ ) ; 
 char* input ; 
 int /*<<< orphan*/  mux ; 
 char* output ; 
 scalar_t__ par_height ; 
 scalar_t__ par_width ; 
 int /*<<< orphan*/ * preset_export_desc ; 
 int /*<<< orphan*/ * preset_export_file ; 
 int /*<<< orphan*/ * preset_export_name ; 
 int /*<<< orphan*/ * queue_import_name ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * strdup (int /*<<< orphan*/ ) ; 
 char* strrchr (char*,char) ; 
 int subtitle_all ; 
 int /*<<< orphan*/ * subtitle_lang_list ; 
 int /*<<< orphan*/  subtracks ; 
 scalar_t__ titleindex ; 
 int /*<<< orphan*/  titlescan ; 

__attribute__((used)) static int CheckOptions( int argc, char ** argv )
{
    if (queue_import_name != NULL)
    {
        // Everything should be defined in the queue.
        return 0;
    }

    if (preset_export_name == NULL && (input == NULL || *input == '\0'))
    {
        fprintf( stderr, "Missing input device. Run %s --help for "
                 "syntax.\n", argv[0] );
        return 1;
    }

    /* Parse format */
    if (titleindex > 0 && !titlescan)
    {
        if (preset_export_name == NULL && (output == NULL || *output == '\0'))
        {
            fprintf( stderr, "Missing output file name. Run %s --help "
                     "for syntax.\n", argv[0] );
            return 1;
        }

        if (format == NULL && output != NULL)
        {
            /* autodetect */
            const char *extension = strrchr(output, '.');
            if (extension != NULL)
            {
                // skip '.'
                mux = hb_container_get_from_extension(extension + 1);
            }
            hb_container_t * c = hb_container_get_from_format(mux);
            if (c != NULL)
                format = strdup(c->short_name);
        }
    }

    int subtitle_track_count = count_subtitles(subtracks);
    if (subtitle_track_count > 0 && subtitle_lang_list != NULL)
    {
        fprintf(stderr,
                "Incompatible options: --subtitle-lang-list and --subtitle\n");
        return 1;
    }

    if (subtitle_track_count > 0 && subtitle_all != -1)
    {
        fprintf(stderr,
                "Incompatible options: --all-subtitles/--first-subtitle and --subtitle\n");
        return 1;
    }

    if (atracks != NULL && audio_lang_list != NULL)
    {
        fprintf(stderr,
                "Incompatible options: --audio-lang-list and --audio\n");
        return 1;
    }

    if (atracks != NULL && audio_all != -1)
    {
        fprintf(stderr,
                "Incompatible options: --all-audio/--first-audio and --audio\n");
        return 1;
    }

    if ((par_width > 0 && par_height > 0) && display_width > 0)
    {
        fprintf(stderr,
                "Incompatible options: --display-width and --pixel-aspect\n");
        return 1;
    }

    if (preset_export_file != NULL && preset_export_name == NULL)
    {
        fprintf(stderr,
                "Error: --preset-export-file requires option --preset-export\n");
        return 1;
    }

    if (preset_export_desc != NULL && preset_export_name == NULL)
    {
        fprintf(stderr,
                "Error: --preset-export-desc requires option --preset-export\n");
        return 1;
    }

    return 0;
}