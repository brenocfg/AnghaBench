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
struct passwd {int dummy; } ;
typedef  scalar_t__ apr_status_t ;

/* Variables and functions */
 scalar_t__ APR_ENOENT ; 
 scalar_t__ APR_SUCCESS ; 
 int /*<<< orphan*/  PWBUF_SIZE ; 
 scalar_t__ errno ; 
 struct passwd* getpwnam (char const*) ; 
 scalar_t__ getpwnam_r (char const*,struct passwd*,char*,int /*<<< orphan*/ ,struct passwd**) ; 
 int /*<<< orphan*/  memcpy (struct passwd*,struct passwd*,int) ; 

__attribute__((used)) static apr_status_t getpwnam_safe(const char *username,
                                  struct passwd *pw,
                                  char pwbuf[PWBUF_SIZE])
{
    struct passwd *pwptr;
#if APR_HAS_THREADS && defined(_POSIX_THREAD_SAFE_FUNCTIONS) && defined(HAVE_GETPWNAM_R)
    apr_status_t rv;

    /* POSIX defines getpwnam_r() et al to return the error number
     * rather than set errno, and requires pwptr to be set to NULL if
     * the entry is not found, imply that "not found" is not an error
     * condition; some implementations do return 0 with pwptr set to
     * NULL. */
    rv = getpwnam_r(username, pw, pwbuf, PWBUF_SIZE, &pwptr);
    if (rv) {
        return rv;
    }
    if (pwptr == NULL) {
        return APR_ENOENT;
    }
#else
    /* Some platforms (e.g. FreeBSD 4.x) do not set errno on NULL "not
     * found" return values for the non-threadsafe function either. */
    errno = 0;
    if ((pwptr = getpwnam(username)) != NULL) {
        memcpy(pw, pwptr, sizeof *pw);
    }
    else {
        return errno ? errno : APR_ENOENT;
    }
#endif
    return APR_SUCCESS;
}