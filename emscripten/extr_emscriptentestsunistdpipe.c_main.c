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

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ ESPIPE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  F_SETFL ; 
 int /*<<< orphan*/  O_NONBLOCK ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  buf ; 
 scalar_t__ errno ; 
 scalar_t__ fcntl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ pipe (int*) ; 
 int /*<<< orphan*/  puts (char*) ; 
 int read (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  test_poll (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_read (int,unsigned char*,int) ; 
 int /*<<< orphan*/  test_write (int,unsigned char*,int) ; 
 int write (int,int /*<<< orphan*/ ,int) ; 

int main()
{
    int fd[2];
    unsigned char wchar = 0;
    unsigned char rchar = 0;

    assert(pipe(fd) == 0);

    // Test that pipe is not seekable

    memset(buf, 0, sizeof buf);
    assert(write(fd[1], buf, 128) == 128);
    assert(lseek(fd[0], 0, SEEK_CUR) == -1);
    assert(errno == ESPIPE);
    assert(lseek(fd[1], 0, SEEK_CUR) == -1);
    assert(errno == ESPIPE);
    assert(read(fd[0], buf, sizeof buf) == 128);

    // Now pipe is empty
    // Test interleaved writing and reading of different buffer sizes

    for(int i = 1; i < 200; ++i) // write about 40 Kb of data
    {
        test_write(fd[1], &wchar, i + 2);
        test_poll(fd, TRUE);
        test_read (fd[0], &rchar, i);
        test_poll(fd, TRUE);
        test_write(fd[1], &wchar, i + 1);
        test_poll(fd, TRUE);
        test_read (fd[0], &rchar, i + 3);
        test_poll(fd, FALSE);
    }

    // Test reading when there is less data available than the read buffer size

    assert(write(fd[1], buf, 10) == 10);
    assert(read(fd[0], buf, sizeof buf) == 10);

    // Write total of 1 Mb of data in small chunks
    // The pipe should not overflow

    int bytes_to_write = 1 << 20;
    while(bytes_to_write > 0)
    {
        test_write(fd[1], &wchar, sizeof buf);
        test_read (fd[0], &rchar, sizeof buf);
        bytes_to_write -= sizeof buf;
    }

    // Write large chunks of data (supposed to be larger than one internal buffer)
    test_write(fd[1], &wchar, 123);
    test_write(fd[1], &wchar, (1 << 15) + 321);
    test_write(fd[1], &wchar, 456);
    test_read(fd[0], &rchar, 456);
    test_read(fd[0], &rchar, (1 << 15) + 123);
    test_read(fd[0], &rchar, 321);


    // Test non-blocking read from empty pipe

    assert(fcntl(fd[0], F_SETFL, O_NONBLOCK) == 0);
    assert(read(fd[0], buf, sizeof buf) == -1);
    assert(errno == EAGAIN);

    // Normal operations still work in non-blocking mode

    test_poll(fd, FALSE);
    test_write(fd[1], &wchar, 10);
    test_poll(fd, TRUE);
    test_read (fd[0], &rchar, 10);
    test_poll(fd, FALSE);

    puts("success");

    return 0;
}