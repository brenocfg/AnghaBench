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
struct representation {struct fragment* init_section; } ;
struct fragment {char* url; scalar_t__ url_offset; scalar_t__ size; } ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 scalar_t__ av_strcasecmp (char*,char*) ; 

__attribute__((used)) static int is_common_init_section_exist(struct representation **pls, int n_pls)
{
    struct fragment *first_init_section = pls[0]->init_section;
    char *url =NULL;
    int64_t url_offset = -1;
    int64_t size = -1;
    int i = 0;

    if (first_init_section == NULL || n_pls == 0)
        return 0;

    url = first_init_section->url;
    url_offset = first_init_section->url_offset;
    size = pls[0]->init_section->size;
    for (i=0;i<n_pls;i++) {
        if (av_strcasecmp(pls[i]->init_section->url,url) || pls[i]->init_section->url_offset != url_offset || pls[i]->init_section->size != size) {
            return 0;
        }
    }
    return 1;
}