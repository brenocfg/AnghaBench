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
struct TYPE_3__ {int /*<<< orphan*/  package_uid; int /*<<< orphan*/  package_ul; } ;
typedef  TYPE_1__ MXFPackage ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int /*<<< orphan*/  AV_DICT_DONT_STRDUP_VAL ; 
 int /*<<< orphan*/  av_dict_set (int /*<<< orphan*/ **,char const*,char*,int /*<<< orphan*/ ) ; 
 int mxf_umid_to_str (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 

__attribute__((used)) static int mxf_add_umid_metadata(AVDictionary **pm, const char *key, MXFPackage* package)
{
    char *str;
    int ret;
    if (!package)
        return 0;
    if ((ret = mxf_umid_to_str(package->package_ul, package->package_uid, &str)) < 0)
        return ret;
    av_dict_set(pm, key, str, AV_DICT_DONT_STRDUP_VAL);
    return 0;
}