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

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 char* GetEnv (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  geteuid () ; 
 struct passwd* getpwuid (int /*<<< orphan*/ ) ; 
 char* strdup (char*) ; 

char *homedir(void)
{
  char *home;

  home = GetEnv("CURL_HOME", FALSE);
  if(home)
    return home;

  home = GetEnv("HOME", FALSE);
  if(home)
    return home;

#if defined(HAVE_GETPWUID) && defined(HAVE_GETEUID)
 {
   struct passwd *pw = getpwuid(geteuid());

   if(pw) {
     home = pw->pw_dir;
     if(home && home[0])
       home = strdup(home);
     else
       home = NULL;
   }
 }
#endif /* PWD-stuff */
#ifdef WIN32
  home = GetEnv("APPDATA", TRUE);
  if(!home)
    home = GetEnv("%USERPROFILE%\\Application Data", TRUE); /* Normally only
                                                               on Win-2K/XP */
#endif /* WIN32 */
  return home;
}