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
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ AVCodec ;

/* Variables and functions */
 TYPE_1__* av_codec_iterate (void**) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static AVCodec *find_codec_by_name(const char *name, int (*x)(const AVCodec *))
{
    void *i = 0;
    const AVCodec *p;

    if (!name)
        return NULL;

    while ((p = av_codec_iterate(&i))) {
        if (!x(p))
            continue;
        if (strcmp(name, p->name) == 0)
            return (AVCodec*)p;
    }

    return NULL;
}