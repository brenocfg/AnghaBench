#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ sqlite3_int64 ;
struct TYPE_8__ {TYPE_1__* pMethods; } ;
typedef  TYPE_2__ sqlite3_file ;
struct TYPE_9__ {int bUseFetch; scalar_t__ szMmap; TYPE_2__* fd; } ;
struct TYPE_7__ {int iVersion; } ;
typedef  TYPE_3__ Pager ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_FCNTL_MMAP_SIZE ; 
 scalar_t__ isOpen (TYPE_2__*) ; 
 int /*<<< orphan*/  sqlite3OsFileControlHint (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static void pagerFixMaplimit(Pager *pPager){
#if SQLITE_MAX_MMAP_SIZE>0
  sqlite3_file *fd = pPager->fd;
  if( isOpen(fd) ){
    sqlite3_int64 sz;
    pPager->bUseFetch = (fd->pMethods->iVersion>=3) && pPager->szMmap>0;
    sz = pPager->szMmap;
    sqlite3OsFileControlHint(pPager->fd, SQLITE_FCNTL_MMAP_SIZE, &sz);
  }
#endif
}