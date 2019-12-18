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
struct passwd {char* pw_dir; } ;
typedef  int /*<<< orphan*/  pwbuf ;

/* Variables and functions */
 int /*<<< orphan*/  DIR_CHAR ; 
 int NETRC_FILE_MISSING ; 
 char* curl_getenv (char*) ; 
 char* curl_maprintf (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  geteuid () ; 
 struct passwd* getpwuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getpwuid_r (int /*<<< orphan*/ ,struct passwd*,char*,int,struct passwd**) ; 
 int parsenetrc (char const*,char**,char**,int*,int*,char*) ; 

int Curl_parsenetrc(const char *host,
                    char **loginp,
                    char **passwordp,
                    bool *login_changed,
                    bool *password_changed,
                    char *netrcfile)
{
  int retcode = 1;
  char *filealloc = NULL;

  if(!netrcfile) {
    char *home = NULL;
    char *homea = curl_getenv("HOME"); /* portable environment reader */
    if(homea) {
      home = homea;
#if defined(HAVE_GETPWUID_R) && defined(HAVE_GETEUID)
    }
    else {
      struct passwd pw, *pw_res;
      char pwbuf[1024];
      if(!getpwuid_r(geteuid(), &pw, pwbuf, sizeof(pwbuf), &pw_res)
         && pw_res) {
        home = pw.pw_dir;
      }
#elif defined(HAVE_GETPWUID) && defined(HAVE_GETEUID)
    }
    else {
      struct passwd *pw;
      pw = getpwuid(geteuid());
      if(pw) {
        home = pw->pw_dir;
      }
#endif
    }

    if(!home)
      return retcode; /* no home directory found (or possibly out of
                         memory) */

    filealloc = curl_maprintf("%s%s.netrc", home, DIR_CHAR);
    if(!filealloc) {
      free(homea);
      return -1;
    }
    retcode = parsenetrc(host, loginp, passwordp, login_changed,
                         password_changed, filealloc);
    free(filealloc);
#ifdef WIN32
    if(retcode == NETRC_FILE_MISSING) {
      /* fallback to the old-style "_netrc" file */
      filealloc = curl_maprintf("%s%s_netrc", home, DIR_CHAR);
      if(!filealloc) {
        free(homea);
        return -1;
      }
      retcode = parsenetrc(host, loginp, passwordp, login_changed,
                           password_changed, filealloc);
      free(filealloc);
    }
#endif
    free(homea);
  }
  else
    retcode = parsenetrc(host, loginp, passwordp, login_changed,
                         password_changed, netrcfile);
  return retcode;
}