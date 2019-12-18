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
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  GetStdHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReadFile (int /*<<< orphan*/ ,unsigned char*,size_t,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STD_INPUT_HANDLE ; 
 int /*<<< orphan*/  dump_blob (char*,unsigned char*,size_t) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ read (int /*<<< orphan*/ ,unsigned char*,size_t) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ verbose ; 

__attribute__((used)) static int
stdin_read(void *ctx, unsigned char *buf, size_t len)
{
	for (;;) {
#ifdef _WIN32
		DWORD rlen;
#else
		ssize_t rlen;
#endif
		int eof;

#ifdef _WIN32
		eof = !ReadFile(GetStdHandle(STD_INPUT_HANDLE),
			buf, len, &rlen, NULL) || rlen == 0;
#else
		rlen = read(0, buf, len);
		if (rlen <= 0) {
			if (rlen < 0 && errno == EINTR) {
				continue;
			}
			eof = 1;
		} else {
			eof = 0;
		}
#endif
		if (eof) {
			if (*(int *)ctx) {
				if (verbose) {
					fprintf(stderr, "recv: EOF\n");
				}
			}
			return -1;
		}
		if (*(int *)ctx) {
			dump_blob("recv", buf, (size_t)rlen);
		}
		return (int)rlen;
	}
}