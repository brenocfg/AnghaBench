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
struct TYPE_2__ {int /*<<< orphan*/ * files; } ;
typedef  TYPE_1__ vfs_fat_ctx_t ;
struct stat {int st_mode; scalar_t__ st_ctime; scalar_t__ st_atime; scalar_t__ st_mtime; int /*<<< orphan*/  st_size; } ;
typedef  int /*<<< orphan*/  FIL ;

/* Variables and functions */
 int S_IFREG ; 
 int S_IRWXG ; 
 int S_IRWXO ; 
 int S_IRWXU ; 
 int /*<<< orphan*/  f_size (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vfs_fat_fstat(void* ctx, int fd, struct stat * st)
{
    vfs_fat_ctx_t* fat_ctx = (vfs_fat_ctx_t*) ctx;
    FIL* file = &fat_ctx->files[fd];
    st->st_size = f_size(file);
    st->st_mode = S_IRWXU | S_IRWXG | S_IRWXO | S_IFREG;
    st->st_mtime = 0;
    st->st_atime = 0;
    st->st_ctime = 0;
    return 0;
}