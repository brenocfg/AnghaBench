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
typedef  int /*<<< orphan*/  tmp_str ;
struct segment {int size; void* url_offset; int /*<<< orphan*/  url; } ;
struct playlist {int /*<<< orphan*/  n_init_sections; int /*<<< orphan*/  init_sections; } ;
struct init_section_info {char* byterange; int /*<<< orphan*/ * uri; } ;

/* Variables and functions */
 int MAX_URL_SIZE ; 
 int /*<<< orphan*/  av_free (struct segment*) ; 
 struct segment* av_mallocz (int) ; 
 int /*<<< orphan*/  av_strdup (char*) ; 
 int /*<<< orphan*/  dynarray_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct segment*) ; 
 int /*<<< orphan*/  ff_make_absolute_url (char*,int,char const*,int /*<<< orphan*/ *) ; 
 char* strchr (char*,char) ; 
 void* strtoll (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static struct segment *new_init_section(struct playlist *pls,
                                        struct init_section_info *info,
                                        const char *url_base)
{
    struct segment *sec;
    char *ptr;
    char tmp_str[MAX_URL_SIZE];

    if (!info->uri[0])
        return NULL;

    sec = av_mallocz(sizeof(*sec));
    if (!sec)
        return NULL;

    ff_make_absolute_url(tmp_str, sizeof(tmp_str), url_base, info->uri);
    sec->url = av_strdup(tmp_str);
    if (!sec->url) {
        av_free(sec);
        return NULL;
    }

    if (info->byterange[0]) {
        sec->size = strtoll(info->byterange, NULL, 10);
        ptr = strchr(info->byterange, '@');
        if (ptr)
            sec->url_offset = strtoll(ptr+1, NULL, 10);
    } else {
        /* the entire file is the init section */
        sec->size = -1;
    }

    dynarray_add(&pls->init_sections, &pls->n_init_sections, sec);

    return sec;
}