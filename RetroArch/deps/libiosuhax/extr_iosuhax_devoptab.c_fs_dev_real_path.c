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
struct TYPE_3__ {char const* mount_path; } ;
typedef  TYPE_1__ fs_dev_private_t ;

/* Variables and functions */
 scalar_t__ malloc (int) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static char *fs_dev_real_path (const char *path, fs_dev_private_t *dev)
{
    /* Sanity check */
    if (!path || !dev)
        return NULL;

    /* Move the path pointer to the start of the actual path */
    if (strchr(path, ':') != NULL) {
        path = strchr(path, ':') + 1;
    }

    int mount_len = strlen(dev->mount_path);

    char *new_name = (char*)malloc(mount_len + strlen(path) + 1);
    if(new_name) {
        strcpy(new_name, dev->mount_path);
        strcpy(new_name + mount_len, path);
        return new_name;
    }
    return new_name;
}