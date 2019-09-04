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
typedef  int uint64_t ;
typedef  int int64_t ;
struct TYPE_4__ {int layout; scalar_t__ name; } ;

/* Variables and functions */
 int FFMAX (int,int /*<<< orphan*/ ) ; 
 int FF_ARRAY_ELEMS (TYPE_1__*) ; 
 int av_get_default_channel_layout (int) ; 
 TYPE_1__* channel_layout_map ; 
 TYPE_1__* channel_names ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  memcmp (scalar_t__,char const*,int) ; 
 int strlen (scalar_t__) ; 
 int strtol (char const*,char**,int) ; 
 int strtoll (char const*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint64_t get_channel_layout_single(const char *name, int name_len)
{
    int i;
    char *end;
    int64_t layout;

    for (i = 0; i < FF_ARRAY_ELEMS(channel_layout_map); i++) {
        if (strlen(channel_layout_map[i].name) == name_len &&
            !memcmp(channel_layout_map[i].name, name, name_len))
            return channel_layout_map[i].layout;
    }
    for (i = 0; i < FF_ARRAY_ELEMS(channel_names); i++)
        if (channel_names[i].name &&
            strlen(channel_names[i].name) == name_len &&
            !memcmp(channel_names[i].name, name, name_len))
            return (int64_t)1 << i;

    errno = 0;
    i = strtol(name, &end, 10);

    if (!errno && (end + 1 - name == name_len && *end  == 'c'))
        return av_get_default_channel_layout(i);

    errno = 0;
    layout = strtoll(name, &end, 0);
    if (!errno && end - name == name_len)
        return FFMAX(layout, 0);
    return 0;
}