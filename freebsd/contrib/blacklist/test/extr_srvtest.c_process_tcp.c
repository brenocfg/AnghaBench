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
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int /*<<< orphan*/  b ; 
 int /*<<< orphan*/  blacklist (int,int,char*) ; 
 int /*<<< orphan*/  blacklist_r (int /*<<< orphan*/ ,int,int,char*) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 char* getprogname () ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,char*,int,char*) ; 
 int read (int,char*,int) ; 

__attribute__((used)) static void
process_tcp(int afd)
{
	ssize_t n;
	char buffer[256];

	memset(buffer, 0, sizeof(buffer));

	if ((n = read(afd, buffer, sizeof(buffer))) == -1)
		err(1, "read");
	buffer[sizeof(buffer) - 1] = '\0';
	printf("%s: sending %d %s\n", getprogname(), afd, buffer);
#ifdef BLDEBUG
	blacklist_r(b, 1, afd, buffer);
#else
	blacklist(1, afd, buffer);
#endif
	exit(0);
}