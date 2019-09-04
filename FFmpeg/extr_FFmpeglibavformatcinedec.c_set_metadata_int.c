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
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int av_dict_set_int (int /*<<< orphan*/ **,char const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_metadata_int(AVDictionary **dict, const char *key, int value, int allow_zero)
{
    if (value || allow_zero) {
        return av_dict_set_int(dict, key, value, 0);
    }
    return 0;
}