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
typedef  int /*<<< orphan*/  iop_file_t ;
struct TYPE_2__ {int /*<<< orphan*/ * fd; } ;

/* Variables and functions */
 TYPE_1__* fd_table ; 
 scalar_t__* fd_used ; 
 int /*<<< orphan*/  files_open ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int CDVD_close(iop_file_t *f)
{
    int i;

#ifdef DEBUG
    printf("CDVD: fd_close called.\n");
    printf("      kernel fd.. %p\n\n", f);
#endif

    for (i = 0; i < 16; i++) {
        if (fd_table[i].fd == f)
            break;
    }

    if (i >= 16) {
#ifdef DEBUG
        printf("CDVD_close: ERROR: File does not appear to be open!\n");
#endif

        return -1;
    }

#ifdef DEBUG
    printf("CDVD: internal fd %d\n", i);
#endif

    fd_used[i] = 0;
    files_open--;

    return 0;
}