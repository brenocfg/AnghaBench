#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* url; } ;
typedef  TYPE_1__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_freep (char**) ; 
 char* av_strdup (char*) ; 
 int ff_rename (char*,char*,TYPE_1__*) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static int hls_rename_temp_file(AVFormatContext *s, AVFormatContext *oc)
{
    size_t len = strlen(oc->url);
    char *final_filename = av_strdup(oc->url);
    int ret;

    if (!final_filename)
        return AVERROR(ENOMEM);
    final_filename[len-4] = '\0';
    ret = ff_rename(oc->url, final_filename, s);
    oc->url[len-4] = '\0';
    av_freep(&final_filename);
    return ret;
}