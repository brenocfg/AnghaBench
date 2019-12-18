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
struct TYPE_2__ {int filePos; int fileSize; int /*<<< orphan*/ * fd; } ;

/* Variables and functions */
#define  SEEK_CUR 130 
#define  SEEK_END 129 
#define  SEEK_SET 128 
 TYPE_1__* fd_table ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int CDVD_lseek(iop_file_t *f, int offset, int whence)
{
    int i;

#ifdef DEBUG
    printf("CDVD: fd_seek called.\n");
    printf("      kernel_fd... %p\n", f);
    printf("      offset...... %d\n", offset);
    printf("      whence...... %d\n\n", whence);
#endif

    for (i = 0; i < 16; i++) {
        if (fd_table[i].fd == f)
            break;
    }

    if (i >= 16) {
#ifdef DEBUG
        printf("CDVD_lseek: ERROR: File does not appear to be open!\n");
#endif

        return -1;
    }

    switch (whence) {
        case SEEK_SET:
            fd_table[i].filePos = offset;
            break;

        case SEEK_CUR:
            fd_table[i].filePos += offset;
            break;

        case SEEK_END:
            fd_table[i].filePos = fd_table[i].fileSize + offset;
            break;

        default:
            return -1;
    }

    if (fd_table[i].filePos < 0)
        fd_table[i].filePos = 0;

    if (fd_table[i].filePos > fd_table[i].fileSize)
        fd_table[i].filePos = fd_table[i].fileSize;

    return fd_table[i].filePos;
}