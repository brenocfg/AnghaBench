#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int O_BINARY ; 
 int O_RDONLY ; 
 int SIZE ; 
 char* av_hash_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_hash_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_hash_update (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int /*<<< orphan*/  finish () ; 
 int /*<<< orphan*/  hash ; 
 int open (char*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int read (int,int /*<<< orphan*/ *,int) ; 
 char* strerror (int) ; 

__attribute__((used)) static int check(char *file)
{
    uint8_t buffer[SIZE];
    int fd, flags = O_RDONLY;
    int ret = 0;

#ifdef O_BINARY
    flags |= O_BINARY;
#endif
    if (file) fd = open(file, flags);
    else      fd = 0;
    if (fd == -1) {
        printf("%s=OPEN-FAILED: %s:", av_hash_get_name(hash), strerror(errno));
        ret = 1;
        goto end;
    }

    av_hash_init(hash);
    for (;;) {
        int size = read(fd, buffer, SIZE);
        if (size < 0) {
            int err = errno;
            close(fd);
            finish();
            printf("+READ-FAILED: %s", strerror(err));
            ret = 2;
            goto end;
        } else if(!size)
            break;
        av_hash_update(hash, buffer, size);
    }
    close(fd);

    finish();
end:
    if (file)
        printf(" *%s", file);
    printf("\n");

    return ret;
}