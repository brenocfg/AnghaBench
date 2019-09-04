#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int sectorSize; int /*<<< orphan*/  fd; scalar_t__ tempFile; } ;
typedef  TYPE_1__ Pager ;

/* Variables and functions */
 int MAX_SECTOR_SIZE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ isOpen (int /*<<< orphan*/ ) ; 
 int sqlite3OsSectorSize (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void setSectorSize(Pager *pPager){
  assert( isOpen(pPager->fd) || pPager->tempFile );

  if( !pPager->tempFile ){
    /* Sector size doesn't matter for temporary files. Also, the file
    ** may not have been opened yet, in which case the OsSectorSize()
    ** call will segfault.
    */
    pPager->sectorSize = sqlite3OsSectorSize(pPager->fd);
  }
  if( pPager->sectorSize<32 ){
    pPager->sectorSize = 512;
  }
  if( pPager->sectorSize>MAX_SECTOR_SIZE ){
    assert( MAX_SECTOR_SIZE>=512 );
    pPager->sectorSize = MAX_SECTOR_SIZE;
  }
}