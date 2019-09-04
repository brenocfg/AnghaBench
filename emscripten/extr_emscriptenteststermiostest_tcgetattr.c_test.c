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
struct termios {int dummy; } ;

/* Variables and functions */
 int ENOTTY ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int STDIN_FILENO ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  puts (char*) ; 
 int tcgetattr (int,struct termios*) ; 
 int tcsetattr (int,int /*<<< orphan*/ ,struct termios*) ; 

void test() {
	struct termios tc;
	int ret;
	int fd;

	fd = open("test.txt", O_RDONLY);

	ret = tcgetattr(fd, &tc);
	assert(ret == -1);
	assert(errno = ENOTTY);

	ret = tcgetattr(STDIN_FILENO, &tc);
	assert(!ret);

	ret = tcsetattr(fd, 0, &tc);
	assert(ret == -1);
	assert(errno = ENOTTY);

	ret = tcsetattr(STDIN_FILENO, 0, &tc);
	assert(!ret);

	close(fd);

	puts("success");
}