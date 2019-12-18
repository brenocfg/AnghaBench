#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ssize_t ;
struct TYPE_9__ {char* path; int /*<<< orphan*/  dir_end; } ;
typedef  TYPE_1__ sqfs_traverse ;
typedef  scalar_t__ sqfs_err ;
struct TYPE_10__ {int /*<<< orphan*/  fd; } ;
typedef  TYPE_2__ sqfs ;

/* Variables and functions */
 scalar_t__ SQFS_OK ; 
 scalar_t__ appimage_get_elf_size (char*) ; 
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  sqfs_fd_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqfs_inode_root (TYPE_2__*) ; 
 scalar_t__ sqfs_open_image (TYPE_2__*,char*,scalar_t__) ; 
 int /*<<< orphan*/  sqfs_traverse_close (TYPE_1__*) ; 
 scalar_t__ sqfs_traverse_next (TYPE_1__*,scalar_t__*) ; 
 scalar_t__ sqfs_traverse_open (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ) ; 

int sfs_ls(char* image) {
    sqfs_err err = SQFS_OK;
    sqfs_traverse trv;
    sqfs fs;
    
    ssize_t fs_offset = appimage_get_elf_size(image);

    // error check
    if (fs_offset < 0)
        die("failed to read elf size");

    if ((err = sqfs_open_image(&fs, image, fs_offset)))
        die("sqfs_open_image error");
    
    if ((err = sqfs_traverse_open(&trv, &fs, sqfs_inode_root(&fs))))
        die("sqfs_traverse_open error");
    while (sqfs_traverse_next(&trv, &err)) {
        if (!trv.dir_end) {
            printf("%s\n", trv.path);
        }
    }
    if (err)
        die("sqfs_traverse_next error");
    sqfs_traverse_close(&trv);
    
    sqfs_fd_close(fs.fd);
    return 0;
}