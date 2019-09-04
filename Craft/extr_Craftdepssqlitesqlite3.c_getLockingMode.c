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
 int PAGER_LOCKINGMODE_EXCLUSIVE ; 
 int PAGER_LOCKINGMODE_NORMAL ; 
 int PAGER_LOCKINGMODE_QUERY ; 
 scalar_t__ sqlite3StrICmp (char const*,char*) ; 

__attribute__((used)) static int getLockingMode(const char *z){
  if( z ){
    if( 0==sqlite3StrICmp(z, "exclusive") ) return PAGER_LOCKINGMODE_EXCLUSIVE;
    if( 0==sqlite3StrICmp(z, "normal") ) return PAGER_LOCKINGMODE_NORMAL;
  }
  return PAGER_LOCKINGMODE_QUERY;
}