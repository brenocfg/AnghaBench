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
typedef  int wchar_t ;
typedef  int /*<<< orphan*/  wbuf ;
typedef  int /*<<< orphan*/  buffer ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGASSERT (int) ; 
 int FORMAT_MESSAGE_FROM_SYSTEM ; 
 int FORMAT_MESSAGE_IGNORE_INSERTS ; 
 int /*<<< orphan*/  FormatMessage (int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FormatMessageA (int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  LANG_NEUTRAL ; 
 scalar_t__ OK ; 
 int /*<<< orphan*/  SetLastError (scalar_t__) ; 
 int errno ; 
 int /*<<< orphan*/  get_winsock_error (int,char*,size_t) ; 
 int /*<<< orphan*/  msnprintf (char*,size_t,char*,int,...) ; 
 char* strerror (int) ; 
 scalar_t__ strerror_r (int,char*,...) ; 
 int /*<<< orphan*/  strncpy (char*,char*,size_t) ; 
 char* strrchr (char*,char) ; 
 int sys_nerr ; 
 int /*<<< orphan*/  wcstombs (char*,int*,size_t) ; 

const char *Curl_strerror(int err, char *buf, size_t buflen)
{
#ifdef PRESERVE_WINDOWS_ERROR_CODE
  DWORD old_win_err = GetLastError();
#endif
  int old_errno = errno;
  char *p;
  size_t max;

  DEBUGASSERT(err >= 0);

  max = buflen - 1;
  *buf = '\0';

#ifdef USE_WINSOCK

#ifdef _WIN32_WCE
  {
    wchar_t wbuf[256];
    wbuf[0] = L'\0';

    FormatMessage((FORMAT_MESSAGE_FROM_SYSTEM |
                   FORMAT_MESSAGE_IGNORE_INSERTS), NULL, err,
                  LANG_NEUTRAL, wbuf, sizeof(wbuf)/sizeof(wchar_t), NULL);
    wcstombs(buf, wbuf, max);
  }
#else
  /* 'sys_nerr' is the maximum errno number, it is not widely portable */
  if(err >= 0 && err < sys_nerr)
    strncpy(buf, strerror(err), max);
  else {
    if(!get_winsock_error(err, buf, max) &&
       !FormatMessageA((FORMAT_MESSAGE_FROM_SYSTEM |
                        FORMAT_MESSAGE_IGNORE_INSERTS), NULL, err,
                       LANG_NEUTRAL, buf, (DWORD)max, NULL))
      msnprintf(buf, max, "Unknown error %d (%#x)", err, err);
  }
#endif

#else /* not USE_WINSOCK coming up */

#if defined(HAVE_STRERROR_R) && defined(HAVE_POSIX_STRERROR_R)
 /*
  * The POSIX-style strerror_r() may set errno to ERANGE if insufficient
  * storage is supplied via 'strerrbuf' and 'buflen' to hold the generated
  * message string, or EINVAL if 'errnum' is not a valid error number.
  */
  if(0 != strerror_r(err, buf, max)) {
    if('\0' == buf[0])
      msnprintf(buf, max, "Unknown error %d", err);
  }
#elif defined(HAVE_STRERROR_R) && defined(HAVE_GLIBC_STRERROR_R)
 /*
  * The glibc-style strerror_r() only *might* use the buffer we pass to
  * the function, but it always returns the error message as a pointer,
  * so we must copy that string unconditionally (if non-NULL).
  */
  {
    char buffer[256];
    char *msg = strerror_r(err, buffer, sizeof(buffer));
    if(msg)
      strncpy(buf, msg, max);
    else
      msnprintf(buf, max, "Unknown error %d", err);
  }
#elif defined(HAVE_STRERROR_R) && defined(HAVE_VXWORKS_STRERROR_R)
 /*
  * The vxworks-style strerror_r() does use the buffer we pass to the function.
  * The buffer size should be at least NAME_MAX (256)
  */
  {
    char buffer[256];
    if(OK == strerror_r(err, buffer))
      strncpy(buf, buffer, max);
    else
      msnprintf(buf, max, "Unknown error %d", err);
  }
#else
  {
    char *msg = strerror(err);
    if(msg)
      strncpy(buf, msg, max);
    else
      msnprintf(buf, max, "Unknown error %d", err);
  }
#endif

#endif /* end of ! USE_WINSOCK */

  buf[max] = '\0'; /* make sure the string is zero terminated */

  /* strip trailing '\r\n' or '\n'. */
  p = strrchr(buf, '\n');
  if(p && (p - buf) >= 2)
    *p = '\0';
  p = strrchr(buf, '\r');
  if(p && (p - buf) >= 1)
    *p = '\0';

  if(errno != old_errno)
    errno = old_errno;

#ifdef PRESERVE_WINDOWS_ERROR_CODE
  if(old_win_err != GetLastError())
    SetLastError(old_win_err);
#endif

  return buf;
}