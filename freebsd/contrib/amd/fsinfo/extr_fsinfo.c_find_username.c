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
struct passwd {char* pw_name; } ;

/* Variables and functions */
 char* getenv (char*) ; 
 char* getlogin () ; 
 struct passwd* getpwuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getuid () ; 
 char* xstrdup (char const*) ; 

__attribute__((used)) static char *
find_username(void)
{
  const char *u = getlogin();

  if (!u) {
    struct passwd *pw = getpwuid(getuid());
    if (pw)
      u = pw->pw_name;
  }

  if (!u)
    u = getenv("USER");
  if (!u)
    u = getenv("LOGNAME");
  if (!u)
    u = "root";

  return xstrdup(u);
}