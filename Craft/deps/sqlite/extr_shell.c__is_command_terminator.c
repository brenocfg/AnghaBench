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
 scalar_t__ IsSpace (char const) ; 
 char ToLower (char const) ; 
 scalar_t__ _all_whitespace (char const*) ; 

__attribute__((used)) static int _is_command_terminator(const char *zLine){
  while( IsSpace(zLine[0]) ){ zLine++; };
  if( zLine[0]=='/' && _all_whitespace(&zLine[1]) ){
    return 1;  /* Oracle */
  }
  if( ToLower(zLine[0])=='g' && ToLower(zLine[1])=='o'
         && _all_whitespace(&zLine[2]) ){
    return 1;  /* SQL Server */
  }
  return 0;
}