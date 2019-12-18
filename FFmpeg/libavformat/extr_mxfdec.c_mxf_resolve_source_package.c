#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UID ;
struct TYPE_8__ {int packages_count; int /*<<< orphan*/ * packages_refs; } ;
struct TYPE_7__ {int /*<<< orphan*/  package_uid; int /*<<< orphan*/  package_ul; } ;
typedef  TYPE_1__ MXFPackage ;
typedef  TYPE_2__ MXFContext ;

/* Variables and functions */
 int /*<<< orphan*/  SourcePackage ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* mxf_resolve_strong_ref (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static MXFPackage* mxf_resolve_source_package(MXFContext *mxf, UID package_ul, UID package_uid)
{
    MXFPackage *package = NULL;
    int i;

    for (i = 0; i < mxf->packages_count; i++) {
        package = mxf_resolve_strong_ref(mxf, &mxf->packages_refs[i], SourcePackage);
        if (!package)
            continue;

        if (!memcmp(package->package_ul, package_ul, 16) && !memcmp(package->package_uid, package_uid, 16))
            return package;
    }
    return NULL;
}