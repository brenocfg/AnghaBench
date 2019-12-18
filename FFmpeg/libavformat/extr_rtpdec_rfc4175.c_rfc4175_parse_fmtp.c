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
struct TYPE_3__ {void* depth; int /*<<< orphan*/  sampling; void* height; void* width; } ;
typedef  TYPE_1__ PayloadContext ;
typedef  int /*<<< orphan*/  AVStream ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 void* atoi (char const*) ; 
 int /*<<< orphan*/  av_strdup (char const*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 

__attribute__((used)) static int rfc4175_parse_fmtp(AVFormatContext *s, AVStream *stream,
                              PayloadContext *data, const char *attr,
                              const char *value)
{
    if (!strncmp(attr, "width", 5))
        data->width = atoi(value);
    else if (!strncmp(attr, "height", 6))
        data->height = atoi(value);
    else if (!strncmp(attr, "sampling", 8))
        data->sampling = av_strdup(value);
    else if (!strncmp(attr, "depth", 5))
        data->depth = atoi(value);

    return 0;
}