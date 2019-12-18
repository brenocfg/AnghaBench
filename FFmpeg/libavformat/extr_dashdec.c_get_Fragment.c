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
struct fragment {int size; void* url_offset; } ;

/* Variables and functions */
 struct fragment* av_mallocz (int) ; 
 char* av_strtok (char*,char*,char**) ; 
 void* strtoll (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static struct fragment * get_Fragment(char *range)
{
    struct fragment * seg =  av_mallocz(sizeof(struct fragment));

    if (!seg)
        return NULL;

    seg->size = -1;
    if (range) {
        char *str_end_offset;
        char *str_offset = av_strtok(range, "-", &str_end_offset);
        seg->url_offset = strtoll(str_offset, NULL, 10);
        seg->size = strtoll(str_end_offset, NULL, 10) - seg->url_offset;
    }

    return seg;
}