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
struct stat {scalar_t__ st_size; int st_mode; } ;
typedef  int mode_t ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int FD_CLOEXEC ; 
 int /*<<< orphan*/  F_GETFD ; 
 int /*<<< orphan*/  F_SETFD ; 
 int O_CLOEXEC ; 
 int SQLITE_DEFAULT_FILE_PERMISSIONS ; 
 int SQLITE_MINIMUM_FILE_DESCRIPTOR ; 
 int /*<<< orphan*/  SQLITE_WARNING ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  osClose (int) ; 
 int /*<<< orphan*/  osFchmod (int,int) ; 
 int osFcntl (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ osFstat (int,struct stat*) ; 
 int osOpen (char const*,int,int) ; 
 int /*<<< orphan*/  sqlite3_log (int /*<<< orphan*/ ,char*,char const*,int) ; 

__attribute__((used)) static int robust_open(const char *z, int f, mode_t m){
  int fd;
  mode_t m2 = m ? m : SQLITE_DEFAULT_FILE_PERMISSIONS;
  while(1){
#if defined(O_CLOEXEC)
    fd = osOpen(z,f|O_CLOEXEC,m2);
#else
    fd = osOpen(z,f,m2);
#endif
    if( fd<0 ){
      if( errno==EINTR ) continue;
      break;
    }
    if( fd>=SQLITE_MINIMUM_FILE_DESCRIPTOR ) break;
    osClose(fd);
    sqlite3_log(SQLITE_WARNING, 
                "attempt to open \"%s\" as file descriptor %d", z, fd);
    fd = -1;
    if( osOpen("/dev/null", f, m)<0 ) break;
  }
  if( fd>=0 ){
    if( m!=0 ){
      struct stat statbuf;
      if( osFstat(fd, &statbuf)==0 
       && statbuf.st_size==0
       && (statbuf.st_mode&0777)!=m 
      ){
        osFchmod(fd, m);
      }
    }
#if defined(FD_CLOEXEC) && (!defined(O_CLOEXEC) || O_CLOEXEC==0)
    osFcntl(fd, F_SETFD, osFcntl(fd, F_GETFD, 0) | FD_CLOEXEC);
#endif
  }
  return fd;
}