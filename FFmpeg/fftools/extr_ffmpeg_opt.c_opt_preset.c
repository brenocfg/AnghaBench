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
typedef  int /*<<< orphan*/  tmp_line ;
typedef  int /*<<< orphan*/  line ;
typedef  int /*<<< orphan*/  filename ;
typedef  int /*<<< orphan*/  OptionsContext ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_LOG_FATAL ; 
 int /*<<< orphan*/  MATCH_PER_TYPE_OPT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  av_strlcpy (char*,char*,int) ; 
 int /*<<< orphan*/  av_strtok (char*,char*,char**) ; 
 int /*<<< orphan*/  codec_names ; 
 int /*<<< orphan*/  exit_program (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_preset_file (char*,int,char const*,int,char const*) ; 
 int /*<<< orphan*/  opt_audio_codec (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  opt_data_codec (int /*<<< orphan*/ *,char*,char*) ; 
 scalar_t__ opt_default_new (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  opt_subtitle_codec (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  opt_video_codec (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  str ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 scalar_t__ strcspn (char*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int opt_preset(void *optctx, const char *opt, const char *arg)
{
    OptionsContext *o = optctx;
    FILE *f=NULL;
    char filename[1000], line[1000], tmp_line[1000];
    const char *codec_name = NULL;

    tmp_line[0] = *opt;
    tmp_line[1] = 0;
    MATCH_PER_TYPE_OPT(codec_names, str, codec_name, NULL, tmp_line);

    if (!(f = get_preset_file(filename, sizeof(filename), arg, *opt == 'f', codec_name))) {
        if(!strncmp(arg, "libx264-lossless", strlen("libx264-lossless"))){
            av_log(NULL, AV_LOG_FATAL, "Please use -preset <speed> -qp 0\n");
        }else
            av_log(NULL, AV_LOG_FATAL, "File for preset '%s' not found\n", arg);
        exit_program(1);
    }

    while (fgets(line, sizeof(line), f)) {
        char *key = tmp_line, *value, *endptr;

        if (strcspn(line, "#\n\r") == 0)
            continue;
        av_strlcpy(tmp_line, line, sizeof(tmp_line));
        if (!av_strtok(key,   "=",    &value) ||
            !av_strtok(value, "\r\n", &endptr)) {
            av_log(NULL, AV_LOG_FATAL, "%s: Invalid syntax: '%s'\n", filename, line);
            exit_program(1);
        }
        av_log(NULL, AV_LOG_DEBUG, "ffpreset[%s]: set '%s' = '%s'\n", filename, key, value);

        if      (!strcmp(key, "acodec")) opt_audio_codec   (o, key, value);
        else if (!strcmp(key, "vcodec")) opt_video_codec   (o, key, value);
        else if (!strcmp(key, "scodec")) opt_subtitle_codec(o, key, value);
        else if (!strcmp(key, "dcodec")) opt_data_codec    (o, key, value);
        else if (opt_default_new(o, key, value) < 0) {
            av_log(NULL, AV_LOG_FATAL, "%s: Invalid option or argument: '%s', parsed as '%s' = '%s'\n",
                   filename, line, key, value);
            exit_program(1);
        }
    }

    fclose(f);

    return 0;
}