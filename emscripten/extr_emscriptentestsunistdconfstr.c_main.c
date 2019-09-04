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
 int _CS_GNU_LIBC_VERSION ; 
 int _CS_GNU_LIBPTHREAD_VERSION ; 
 int _CS_PATH ; 
 int _CS_POSIX_V6_ILP32_OFF32_CFLAGS ; 
 int _CS_POSIX_V6_ILP32_OFF32_LDFLAGS ; 
 int _CS_POSIX_V6_ILP32_OFF32_LIBS ; 
 int _CS_POSIX_V6_ILP32_OFFBIG_CFLAGS ; 
 int _CS_POSIX_V6_ILP32_OFFBIG_LDFLAGS ; 
 int _CS_POSIX_V6_ILP32_OFFBIG_LIBS ; 
 int _CS_POSIX_V6_LP64_OFF64_CFLAGS ; 
 int _CS_POSIX_V6_LP64_OFF64_LDFLAGS ; 
 int _CS_POSIX_V6_LP64_OFF64_LIBS ; 
 int _CS_POSIX_V6_LPBIG_OFFBIG_CFLAGS ; 
 int _CS_POSIX_V6_LPBIG_OFFBIG_LDFLAGS ; 
 int _CS_POSIX_V6_LPBIG_OFFBIG_LIBS ; 
 int _CS_POSIX_V6_WIDTH_RESTRICTED_ENVS ; 
 int confstr (int,char*,int) ; 
 int errno ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int main() {
  int vals[] = {
    _CS_PATH,
    _CS_POSIX_V6_WIDTH_RESTRICTED_ENVS,
    _CS_GNU_LIBC_VERSION,
    _CS_GNU_LIBPTHREAD_VERSION,
    _CS_POSIX_V6_ILP32_OFF32_LIBS,
    _CS_POSIX_V6_ILP32_OFFBIG_LIBS,
    _CS_POSIX_V6_LP64_OFF64_CFLAGS,
    _CS_POSIX_V6_LP64_OFF64_LDFLAGS,
    _CS_POSIX_V6_LP64_OFF64_LIBS,
    _CS_POSIX_V6_LPBIG_OFFBIG_CFLAGS,
    _CS_POSIX_V6_LPBIG_OFFBIG_LDFLAGS,
    _CS_POSIX_V6_LPBIG_OFFBIG_LIBS,
    _CS_POSIX_V6_ILP32_OFF32_CFLAGS,
    _CS_POSIX_V6_ILP32_OFF32_LDFLAGS,
    _CS_POSIX_V6_ILP32_OFFBIG_LDFLAGS,
    _CS_POSIX_V6_ILP32_OFFBIG_CFLAGS
  };
  const char* names[] = {
    "_CS_PATH",
    "_CS_POSIX_V6_WIDTH_RESTRICTED_ENVS",
    "_CS_GNU_LIBC_VERSION",
    "_CS_GNU_LIBPTHREAD_VERSION",
    "_CS_POSIX_V6_ILP32_OFF32_LIBS",
    "_CS_POSIX_V6_ILP32_OFFBIG_LIBS",
    "_CS_POSIX_V6_LP64_OFF64_CFLAGS",
    "_CS_POSIX_V6_LP64_OFF64_LDFLAGS",
    "_CS_POSIX_V6_LP64_OFF64_LIBS",
    "_CS_POSIX_V6_LPBIG_OFFBIG_CFLAGS",
    "_CS_POSIX_V6_LPBIG_OFFBIG_LDFLAGS",
    "_CS_POSIX_V6_LPBIG_OFFBIG_LIBS",
    "_CS_POSIX_V6_ILP32_OFF32_CFLAGS",
    "_CS_POSIX_V6_ILP32_OFF32_LDFLAGS",
    "_CS_POSIX_V6_ILP32_OFFBIG_LDFLAGS",
    "_CS_POSIX_V6_ILP32_OFFBIG_CFLAGS"
  };
  char buffer[256];

  for (int i = 0; i < sizeof vals / sizeof vals[0]; i++) {
    printf("ret: %d\n", confstr(vals[i], buffer, 256));
    printf("%s: %s\n", names[i], buffer);
    printf("errno: %d\n\n", errno);
    errno = 0;
  }

  printf("(invalid) ret: %d\n", confstr(-123, buffer, 256));
  printf("errno: %d\n", errno);

  return 0;
}