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
struct dirent {int dummy; } ;
struct TYPE_3__ {struct dirent entry; int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ DIR ;

/* Variables and functions */
 int getdents (int /*<<< orphan*/ ,struct dirent*,int) ; 

struct dirent* readdir( DIR* dir ) {
    int error;

    if ( dir == NULL ) {
        return NULL;
    }

    error = getdents( dir->fd, &dir->entry, sizeof( struct dirent ) );

    if ( error == 0 ) {
        return NULL;
    }

    return &dir->entry;
}