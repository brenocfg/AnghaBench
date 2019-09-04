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
struct TYPE_4__ {unsigned int size; char* str; scalar_t__ len; } ;
typedef  TYPE_1__ AVBPrint ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 unsigned int FFMIN (scalar_t__,unsigned int) ; 
 scalar_t__ av_bprint_is_allocated (TYPE_1__*) ; 
 int /*<<< orphan*/  av_freep (char**) ; 
 char* av_malloc (unsigned int) ; 
 char* av_realloc (char*,unsigned int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,unsigned int) ; 

int av_bprint_finalize(AVBPrint *buf, char **ret_str)
{
    unsigned real_size = FFMIN(buf->len + 1, buf->size);
    char *str;
    int ret = 0;

    if (ret_str) {
        if (av_bprint_is_allocated(buf)) {
            str = av_realloc(buf->str, real_size);
            if (!str)
                str = buf->str;
            buf->str = NULL;
        } else {
            str = av_malloc(real_size);
            if (str)
                memcpy(str, buf->str, real_size);
            else
                ret = AVERROR(ENOMEM);
        }
        *ret_str = str;
    } else {
        if (av_bprint_is_allocated(buf))
            av_freep(&buf->str);
    }
    buf->size = real_size;
    return ret;
}