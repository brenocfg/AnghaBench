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
struct build_version_command {int platform; int /*<<< orphan*/  has_versionmin; int /*<<< orphan*/  minos; int /*<<< orphan*/  version; } ;
typedef  struct build_version_command KXLDversionmin ;

/* Variables and functions */
#define  PLATFORM_IOS 131 
#define  PLATFORM_MACOS 130 
#define  PLATFORM_TVOS 129 
#define  PLATFORM_WATCHOS 128 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  check (struct build_version_command*) ; 
 int kKxldVersionMinAppleTVOS ; 
 int kKxldVersionMinMacOSX ; 
 int kKxldVersionMinWatchOS ; 
 int kKxldVersionMiniPhoneOS ; 

void
kxld_versionmin_init_from_build_cmd(KXLDversionmin *versionmin, struct build_version_command *src)
{
    check(versionmin);
    check(src);
    switch (src->platform) {
    case PLATFORM_MACOS:
        versionmin->platform = kKxldVersionMinMacOSX;
        break;
    case PLATFORM_IOS:
        versionmin->platform = kKxldVersionMiniPhoneOS;
        break;
    case PLATFORM_TVOS:
        versionmin->platform = kKxldVersionMinAppleTVOS;
        break;
    case PLATFORM_WATCHOS:
        versionmin->platform = kKxldVersionMinWatchOS;
        break;
    default:
        return;
    }
    versionmin->version = src->minos;
    versionmin->has_versionmin = TRUE;
}