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
struct utsname {int /*<<< orphan*/  release; } ;

/* Variables and functions */
 int /*<<< orphan*/  frontend_android_get_version (int*,int*,int*) ; 
 int /*<<< orphan*/  sscanf (int /*<<< orphan*/ ,char*,int*,int*,unsigned int*) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,size_t) ; 
 scalar_t__ uname (struct utsname*) ; 

__attribute__((used)) static void frontend_unix_get_os(char *s,
      size_t len, int *major, int *minor)
{
#ifdef ANDROID
   int rel;
   frontend_android_get_version(major, minor, &rel);

   strlcpy(s, "Android", len);
#else
   unsigned krel;
   struct utsname buffer;

   if (uname(&buffer) != 0)
      return;

   sscanf(buffer.release, "%d.%d.%u", major, minor, &krel);
#if defined(__FreeBSD__)
   strlcpy(s, "FreeBSD", len);
#elif defined(__NetBSD__)
   strlcpy(s, "NetBSD", len);
#elif defined(__OpenBSD__)
   strlcpy(s, "OpenBSD", len);
#elif defined(__DragonFly__)
   strlcpy(s, "DragonFly BSD", len);
#elif defined(BSD)
   strlcpy(s, "BSD", len);
#elif defined(__HAIKU__)
   strlcpy(s, "Haiku", len);
#else
   strlcpy(s, "Linux", len);
#endif
#endif
}