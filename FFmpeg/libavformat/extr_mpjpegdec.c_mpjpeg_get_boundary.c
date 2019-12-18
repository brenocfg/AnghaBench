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
typedef  char uint8_t ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_OPT_SEARCH_CHILDREN ; 
 int /*<<< orphan*/  av_freep (char**) ; 
 scalar_t__ av_isspace (char const) ; 
 int /*<<< orphan*/  av_opt_get (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char**) ; 
 scalar_t__ av_stristart (char const*,char*,char const**) ; 
 char* av_strndup (char const*,int) ; 
 char* strchr (char const*,char) ; 
 int strlen (char const*) ; 

__attribute__((used)) static char* mpjpeg_get_boundary(AVIOContext* pb)
{
    uint8_t *mime_type = NULL;
    const char *start;
    const char *end;
    uint8_t *res = NULL;
    int     len;

    /* get MIME type, and skip to the first parameter */
    av_opt_get(pb, "mime_type", AV_OPT_SEARCH_CHILDREN, &mime_type);
    start = mime_type;
    while (start != NULL && *start != '\0') {
        start = strchr(start, ';');
        if (!start)
            break;

        start = start+1;

        while (av_isspace(*start))
            start++;

        if (av_stristart(start, "boundary=", &start)) {
            end = strchr(start, ';');
            if (end)
                len = end - start - 1;
            else
                len = strlen(start);

            /* some endpoints may enclose the boundary
              in Content-Type in quotes */
            if ( len>2 && *start == '"' && start[len-1] == '"' ) {
                start++;
                len -= 2;
            }
            res = av_strndup(start, len);
            break;
        }
    }

    av_freep(&mime_type);
    return res;
}