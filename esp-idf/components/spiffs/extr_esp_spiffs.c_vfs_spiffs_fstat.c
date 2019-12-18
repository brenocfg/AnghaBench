#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct stat {int st_mode; scalar_t__ st_ctime; scalar_t__ st_atime; int /*<<< orphan*/  st_mtime; int /*<<< orphan*/  st_size; } ;
struct TYPE_5__ {int /*<<< orphan*/  size; } ;
typedef  TYPE_1__ spiffs_stat ;
typedef  scalar_t__ off_t ;
struct TYPE_6__ {int /*<<< orphan*/  fs; } ;
typedef  TYPE_2__ esp_spiffs_t ;

/* Variables and functions */
 int /*<<< orphan*/  SPIFFS_clearerr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPIFFS_errno (int /*<<< orphan*/ ) ; 
 scalar_t__ SPIFFS_fstat (int /*<<< orphan*/ ,int,TYPE_1__*) ; 
 int S_IFREG ; 
 int S_IRWXG ; 
 int S_IRWXO ; 
 int S_IRWXU ; 
 int /*<<< orphan*/  assert (struct stat*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  spiffs_res_to_errno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_spiffs_get_mtime (TYPE_1__*) ; 

__attribute__((used)) static int vfs_spiffs_fstat(void* ctx, int fd, struct stat * st)
{
    assert(st);
    spiffs_stat s;
    esp_spiffs_t * efs = (esp_spiffs_t *)ctx;
    off_t res = SPIFFS_fstat(efs->fs, fd, &s);
    if (res < 0) {
        errno = spiffs_res_to_errno(SPIFFS_errno(efs->fs));
        SPIFFS_clearerr(efs->fs);
        return -1;
    }
    st->st_size = s.size;
    st->st_mode = S_IRWXU | S_IRWXG | S_IRWXO | S_IFREG;
    st->st_mtime = vfs_spiffs_get_mtime(&s);
    st->st_atime = 0;
    st->st_ctime = 0;
    return res;
}