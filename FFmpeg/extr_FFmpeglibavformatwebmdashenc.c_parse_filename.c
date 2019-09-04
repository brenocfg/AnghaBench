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
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  ENOMEM ; 
 char* av_asprintf (char*,char*) ; 
 int /*<<< orphan*/  av_freep (char**) ; 
 char* av_malloc (int) ; 
 char* av_strdup (char*) ; 
 char* av_stristr (char*,char*) ; 
 int /*<<< orphan*/  av_strlcpy (char*,char*,int) ; 

__attribute__((used)) static int parse_filename(char *filename, char **representation_id,
                          char **initialization_pattern, char **media_pattern) {
    char *underscore_pos = NULL;
    char *period_pos = NULL;
    char *temp_pos = NULL;
    char *filename_str = av_strdup(filename);
    int ret = 0;

    if (!filename_str) {
        ret = AVERROR(ENOMEM);
        goto end;
    }
    temp_pos = av_stristr(filename_str, "_");
    while (temp_pos) {
        underscore_pos = temp_pos + 1;
        temp_pos = av_stristr(temp_pos + 1, "_");
    }
    if (!underscore_pos) {
        ret = AVERROR_INVALIDDATA;
        goto end;
    }
    period_pos = av_stristr(underscore_pos, ".");
    if (!period_pos) {
        ret = AVERROR_INVALIDDATA;
        goto end;
    }
    *(underscore_pos - 1) = 0;
    if (representation_id) {
        *representation_id = av_malloc(period_pos - underscore_pos + 1);
        if (!(*representation_id)) {
            ret = AVERROR(ENOMEM);
            goto end;
        }
        av_strlcpy(*representation_id, underscore_pos, period_pos - underscore_pos + 1);
    }
    if (initialization_pattern) {
        *initialization_pattern = av_asprintf("%s_$RepresentationID$.hdr",
                                              filename_str);
        if (!(*initialization_pattern)) {
            ret = AVERROR(ENOMEM);
            goto end;
        }
    }
    if (media_pattern) {
        *media_pattern = av_asprintf("%s_$RepresentationID$_$Number$.chk",
                                     filename_str);
        if (!(*media_pattern)) {
            ret = AVERROR(ENOMEM);
            goto end;
        }
    }

end:
    av_freep(&filename_str);
    return ret;
}