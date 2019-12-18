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
typedef  int /*<<< orphan*/  uid_t ;
struct passwd {char* pw_dir; } ;

/* Variables and functions */
 char* getenv (char*) ; 
 struct passwd* getpwuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getuid () ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  sqlite3_snprintf (int,char*,char*,char*,char*) ; 
 int strlen30 (char*) ; 

__attribute__((used)) static char *find_home_dir(void){
  static char *home_dir = NULL;
  if( home_dir ) return home_dir;

#if !defined(_WIN32) && !defined(WIN32) && !defined(_WIN32_WCE) && !defined(__RTP__) && !defined(_WRS_KERNEL)
  {
    struct passwd *pwent;
    uid_t uid = getuid();
    if( (pwent=getpwuid(uid)) != NULL) {
      home_dir = pwent->pw_dir;
    }
  }
#endif

#if defined(_WIN32_WCE)
  /* Windows CE (arm-wince-mingw32ce-gcc) does not provide getenv()
   */
  home_dir = "/";
#else

#if defined(_WIN32) || defined(WIN32)
  if (!home_dir) {
    home_dir = getenv("USERPROFILE");
  }
#endif

  if (!home_dir) {
    home_dir = getenv("HOME");
  }

#if defined(_WIN32) || defined(WIN32)
  if (!home_dir) {
    char *zDrive, *zPath;
    int n;
    zDrive = getenv("HOMEDRIVE");
    zPath = getenv("HOMEPATH");
    if( zDrive && zPath ){
      n = strlen30(zDrive) + strlen30(zPath) + 1;
      home_dir = malloc( n );
      if( home_dir==0 ) return 0;
      sqlite3_snprintf(n, home_dir, "%s%s", zDrive, zPath);
      return home_dir;
    }
    home_dir = "c:\\";
  }
#endif

#endif /* !_WIN32_WCE */

  if( home_dir ){
    int n = strlen30(home_dir) + 1;
    char *z = malloc( n );
    if( z ) memcpy(z, home_dir, n);
    home_dir = z;
  }

  return home_dir;
}