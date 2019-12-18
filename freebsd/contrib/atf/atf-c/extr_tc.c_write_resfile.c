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
struct iovec {char* iov_base; int iov_len; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  atf_error_t ;
typedef  int /*<<< orphan*/  atf_dynstr_t ;
typedef  int /*<<< orphan*/  NL ;
typedef  int /*<<< orphan*/  CS ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  INV (int) ; 
 void* UNCONST (char const*) ; 
 char* atf_dynstr_cstring (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  atf_libc_error (scalar_t__,char*,char const*,char*) ; 
 int /*<<< orphan*/  atf_no_error () ; 
 scalar_t__ errno ; 
 int snprintf (char*,int,char*,int const) ; 
 void* strlen (char const*) ; 
 int writev (int const,struct iovec*,int) ; 

__attribute__((used)) static atf_error_t
write_resfile(const int fd, const char *result, const int arg,
              const atf_dynstr_t *reason)
{
    static char NL[] = "\n", CS[] = ": ";
    char buf[64];
    const char *r;
    struct iovec iov[5];
    ssize_t ret;
    int count = 0;

    INV(arg == -1 || reason != NULL);

#define UNCONST(a) ((void *)(unsigned long)(const void *)(a))
    iov[count].iov_base = UNCONST(result);
    iov[count++].iov_len = strlen(result);

    if (reason != NULL) {
        if (arg != -1) {
            iov[count].iov_base = buf;
            iov[count++].iov_len = snprintf(buf, sizeof(buf), "(%d)", arg);
        }

        iov[count].iov_base = CS;
        iov[count++].iov_len = sizeof(CS) - 1;

        r = atf_dynstr_cstring(reason);
        iov[count].iov_base = UNCONST(r);
        iov[count++].iov_len = strlen(r);
    }
#undef UNCONST

    iov[count].iov_base = NL;
    iov[count++].iov_len = sizeof(NL) - 1;

    while ((ret = writev(fd, iov, count)) == -1 && errno == EINTR)
        continue; /* Retry. */
    if (ret != -1)
        return atf_no_error();

    return atf_libc_error(
        errno, "Failed to write results file; result %s, reason %s", result,
        reason == NULL ? "null" : atf_dynstr_cstring(reason));
}