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
 int /*<<< orphan*/  SPIFFS_clearerr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPIFFS_errno (int /*<<< orphan*/ ) ; 
 int SPIFFS_rename (int /*<<< orphan*/ ,char const*,char const*) ; 
 int /*<<< orphan*/  assert (char const*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  spiffs_res_to_errno (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vfs_spiffs_rename(void* ctx, const char *src, const char *dst)
{
    assert(src);
    assert(dst);
    esp_spiffs_t * efs = (esp_spiffs_t *)ctx;
    int res = SPIFFS_rename(efs->fs, src, dst);
    if (res < 0) {
        errno = spiffs_res_to_errno(SPIFFS_errno(efs->fs));
        SPIFFS_clearerr(efs->fs);
        return -1;
    }
    return res;
}