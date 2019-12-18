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
typedef  long CodedBitstreamUnitType ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_freep (long**) ; 
 long* av_malloc_array (int,int) ; 
 long strtol (char const*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int filter_units_make_type_list(const char *list_string,
                                       CodedBitstreamUnitType **type_list,
                                       int *nb_types)
{
    CodedBitstreamUnitType *list = NULL;
    int pass, count;

    for (pass = 1; pass <= 2; pass++) {
        long value, range_start, range_end;
        const char *str;
        char *value_end;

        count = 0;
        for (str = list_string; *str;) {
            value = strtol(str, &value_end, 0);
            if (str == value_end)
                goto invalid;
            str = (const char *)value_end;
            if (*str == '-') {
                ++str;
                range_start = value;
                range_end   = strtol(str, &value_end, 0);
                if (str == value_end)
                    goto invalid;

                for (value = range_start; value < range_end; value++) {
                    if (pass == 2)
                        list[count] = value;
                    ++count;
                }
            } else {
                if (pass == 2)
                    list[count] = value;
                ++count;
            }
            if (*str == '|')
                ++str;
        }
        if (pass == 1) {
            list = av_malloc_array(count, sizeof(*list));
            if (!list)
                return AVERROR(ENOMEM);
        }
    }

    *type_list = list;
    *nb_types  = count;
    return 0;

invalid:
    av_freep(&list);
    return AVERROR(EINVAL);
}