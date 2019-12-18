#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  fs; } ;
typedef  TYPE_1__ esp_spiffs_t ;

/* Variables and functions */
 int SPIFFS_RDONLY ; 
 int /*<<< orphan*/  SPIFFS_clearerr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPIFFS_errno (int /*<<< orphan*/ ) ; 
 int SPIFFS_open (int /*<<< orphan*/ ,char const*,int,int) ; 
 int /*<<< orphan*/  assert (char const*) ; 
 int /*<<< orphan*/  errno ; 
 int spiffs_mode_conv (int) ; 
 int /*<<< orphan*/  spiffs_res_to_errno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_spiffs_update_mtime (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int vfs_spiffs_open(void* ctx, const char * path, int flags, int mode)
{
    assert(path);
    esp_spiffs_t * efs = (esp_spiffs_t *)ctx;
    int spiffs_flags = spiffs_mode_conv(flags);
    int fd = SPIFFS_open(efs->fs, path, spiffs_flags, mode);
    if (fd < 0) {
        errno = spiffs_res_to_errno(SPIFFS_errno(efs->fs));
        SPIFFS_clearerr(efs->fs);
        return -1;
    }
    if (!(spiffs_flags & SPIFFS_RDONLY)) {
        vfs_spiffs_update_mtime(efs->fs, fd);
    }
    return fd;
}