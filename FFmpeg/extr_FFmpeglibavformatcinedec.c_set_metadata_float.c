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
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int av_dict_set (int /*<<< orphan*/ **,char const*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,float) ; 

__attribute__((used)) static int set_metadata_float(AVDictionary **dict, const char *key, float value, int allow_zero)
{
    if (value != 0 || allow_zero) {
        char tmp[64];
        snprintf(tmp, sizeof(tmp), "%f", value);
        return av_dict_set(dict, key, tmp, 0);
    }
    return 0;
}