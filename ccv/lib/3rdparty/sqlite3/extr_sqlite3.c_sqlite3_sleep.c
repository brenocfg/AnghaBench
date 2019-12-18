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
typedef  int /*<<< orphan*/  sqlite3_vfs ;

/* Variables and functions */
 int sqlite3OsSleep (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * sqlite3_vfs_find (int /*<<< orphan*/ ) ; 

int sqlite3_sleep(int ms){
  sqlite3_vfs *pVfs;
  int rc;
  pVfs = sqlite3_vfs_find(0);
  if( pVfs==0 ) return 0;

  /* This function works in milliseconds, but the underlying OsSleep() 
  ** API uses microseconds. Hence the 1000's.
  */
  rc = (sqlite3OsSleep(pVfs, 1000*ms)/1000);
  return rc;
}