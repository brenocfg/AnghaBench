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
struct stat {int /*<<< orphan*/  st_mode; } ;

/* Variables and functions */
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int rmdir (char const*) ; 
 scalar_t__ stat (char const*,struct stat*) ; 
 int unlink (char const*) ; 

int remove( const char* path ) {
  struct stat st;

  if ( stat( path, &st) != 0 ) {
    return -1;
  }

  if ( S_ISDIR( st.st_mode ) ) {
    return rmdir( path );
  } else {
    return unlink( path );
  }
}