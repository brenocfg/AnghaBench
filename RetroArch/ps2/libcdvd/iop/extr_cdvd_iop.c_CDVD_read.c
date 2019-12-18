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
struct TYPE_2__ {int filePos; int fileSize; int LBA; int /*<<< orphan*/ * fd; } ;

/* Variables and functions */
 scalar_t__ ReadSect (int,int,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  cdReadMode ; 
 TYPE_1__* fd_table ; 
 int last_bk ; 
 int lastsector ; 
 int /*<<< orphan*/  memcpy (void*,char*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int CDVD_read(iop_file_t *f, void *buffer, int size)
{
    int i;

    int start_sector;
    int off_sector;
    int num_sectors;

    int read = 0;
    //	int sector;

    //	int size_left;
    //	int copy_size;

    static char local_buffer[9 * 2048];


#ifdef DEBUG
    printf("CDVD: read called\n");
    printf("      kernel_fd... %p\n", f);
    printf("      buffer...... 0x%X\n", (int)buffer);
    printf("      size........ %d\n\n", size);
#endif

    for (i = 0; i < 16; i++) {
        if (fd_table[i].fd == f)
            break;
    }

    if (i >= 16) {
#ifdef DEBUG
        printf("CDVD_read: ERROR: File does not appear to be open!\n");
#endif

        return -1;
    }


    // A few sanity checks
    if (fd_table[i].filePos > fd_table[i].fileSize) {
        // We cant start reading from past the beginning of the file
        return 0;  // File exists but we couldnt read anything from it
    }

    if ((fd_table[i].filePos + size) > fd_table[i].fileSize)
        size = fd_table[i].fileSize - fd_table[i].filePos;

    if (size <= 0)
        return 0;

    if (size > 16384)
        size = 16384;

    // Now work out where we want to start reading from
    start_sector = fd_table[i].LBA + (fd_table[i].filePos >> 11);
    off_sector = (fd_table[i].filePos & 0x7FF);

    num_sectors = (off_sector + size);
    num_sectors = (num_sectors >> 11) + ((num_sectors & 2047) != 0);

#ifdef DEBUG
    printf("CDVD_read: read sectors %d to %d\n", start_sector, start_sector + num_sectors);
#endif

    // Skip a Sector for equal (use the last sector in buffer)
    if (start_sector == lastsector) {
        read = 1;
        if (last_bk > 0)
            memcpy(local_buffer, local_buffer + 2048 * (last_bk), 2048);
        last_bk = 0;
    }

    lastsector = start_sector + num_sectors - 1;
    // Read the data (we only ever get 16KB max request at once)

    if (read == 0 || (read == 1 && num_sectors > 1)) {
        if (ReadSect(start_sector + read, num_sectors - read, local_buffer + ((read) << 11), &cdReadMode) != TRUE) {
#ifdef DEBUG
            printf("Couldn't Read from file for some reason\n");
#endif
        }

        last_bk = num_sectors - 1;
    }

    memcpy(buffer, local_buffer + off_sector, size);

    fd_table[i].filePos += size;

    return (size);
}