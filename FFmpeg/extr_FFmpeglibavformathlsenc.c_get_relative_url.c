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
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  EINVAL ; 
 int FFABS (int) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  av_strlcpy (char*,char const*,int) ; 
 scalar_t__ av_strncasecmp (char const*,char const*,int) ; 
 char* strrchr (char const*,char) ; 

__attribute__((used)) static int get_relative_url(const char *master_url, const char *media_url,
                            char *rel_url, int rel_url_buf_size)
{
    char *p = NULL;
    int base_len = -1;
    p = strrchr(master_url, '/') ? strrchr(master_url, '/') :\
            strrchr(master_url, '\\');
    if (p) {
        base_len = FFABS(p - master_url);
        if (av_strncasecmp(master_url, media_url, base_len)) {
            av_log(NULL, AV_LOG_WARNING, "Unable to find relative url\n");
            return AVERROR(EINVAL);
        }
    }
    av_strlcpy(rel_url, &(media_url[base_len + 1]), rel_url_buf_size);
    return 0;
}