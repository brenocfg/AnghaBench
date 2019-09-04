#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  url; } ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_1__ AVFormatContext ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EPERM ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int nested_io_open(AVFormatContext *s, AVIOContext **pb, const char *url,
                          int flags, AVDictionary **opts)
{
    av_log(s, AV_LOG_ERROR,
           "A HLS playlist item '%s' referred to an external file '%s'. "
           "Opening this file was forbidden for security reasons\n",
           s->url, url);
    return AVERROR(EPERM);
}