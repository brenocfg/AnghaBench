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
struct TYPE_3__ {char* url; } ;
typedef  TYPE_1__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_assert0 (char*) ; 
 int /*<<< orphan*/  av_freep (char**) ; 

void ff_format_set_url(AVFormatContext *s, char *url)
{
    av_assert0(url);
    av_freep(&s->url);
    s->url = url;
#if FF_API_FORMAT_FILENAME
FF_DISABLE_DEPRECATION_WARNINGS
    av_strlcpy(s->filename, url, sizeof(s->filename));
FF_ENABLE_DEPRECATION_WARNINGS
#endif
}