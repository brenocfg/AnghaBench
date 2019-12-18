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
struct TYPE_3__ {int /*<<< orphan*/  text; } ;
typedef  TYPE_1__ json_error_t ;
typedef  int /*<<< orphan*/  hb_dict_t ;

/* Variables and functions */
 int /*<<< orphan*/  HB_PROJECT_HOST_ARCH ; 
 int /*<<< orphan*/  HB_PROJECT_HOST_SYSTEMF ; 
 int /*<<< orphan*/  HB_PROJECT_NAME ; 
 int /*<<< orphan*/  HB_PROJECT_REPO_DATE ; 
 int /*<<< orphan*/  HB_PROJECT_REPO_HASH ; 
 int /*<<< orphan*/  HB_PROJECT_REPO_OFFICIAL ; 
 int /*<<< orphan*/  HB_PROJECT_REPO_TYPE ; 
 int /*<<< orphan*/  HB_PROJECT_VERSION ; 
 int /*<<< orphan*/  HB_PROJECT_VERSION_MAJOR ; 
 int /*<<< orphan*/  HB_PROJECT_VERSION_MINOR ; 
 int /*<<< orphan*/  HB_PROJECT_VERSION_POINT ; 
 int /*<<< orphan*/  hb_error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_value_bool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_value_int (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_value_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * json_pack_ex (TYPE_1__*,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

hb_dict_t * hb_version_dict()
{
    hb_dict_t * dict;
    json_error_t error;

    dict = json_pack_ex(&error, 0,
        "{s:o, s:o, s:o, s{s:o, s:o, s:o}, s:o, s:o, s:o, s:o, s:o}",
        "Name",          hb_value_string(HB_PROJECT_NAME),
        "Official",      hb_value_bool(HB_PROJECT_REPO_OFFICIAL),
        "Type",          hb_value_string(HB_PROJECT_REPO_TYPE),
        "Version",
            "Major",     hb_value_int(HB_PROJECT_VERSION_MAJOR),
            "Minor",     hb_value_int(HB_PROJECT_VERSION_MINOR),
            "Point",     hb_value_int(HB_PROJECT_VERSION_POINT),
        "VersionString", hb_value_string(HB_PROJECT_VERSION),
        "RepoHash",      hb_value_string(HB_PROJECT_REPO_HASH),
        "RepoDate",      hb_value_string(HB_PROJECT_REPO_DATE),
        "System",        hb_value_string(HB_PROJECT_HOST_SYSTEMF),
        "Arch",          hb_value_string(HB_PROJECT_HOST_ARCH));
    if (dict == NULL)
    {
        hb_error("json pack failure: %s", error.text);
        return NULL;
    }

    return dict;
}