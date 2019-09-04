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
typedef  int uint32_t ;
typedef  TYPE_1__* mount_t ;
struct TYPE_3__ {int mnt_segreadcnt; int mnt_maxreadcnt; int mnt_segwritecnt; int mnt_maxwritecnt; } ;

/* Variables and functions */
#define  CL_READ 129 
#define  CL_WRITE 128 
 int MAX_UPL_SIZE_BYTES ; 
 int MAX_UPL_TRANSFER_BYTES ; 
 int PAGE_MASK ; 
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int min (int,int) ; 

uint32_t
cluster_max_io_size(mount_t mp, int type)
{
	uint32_t	max_io_size;
	uint32_t	segcnt;
	uint32_t	maxcnt;

	switch(type) {

	case CL_READ:
		segcnt = mp->mnt_segreadcnt;
		maxcnt = mp->mnt_maxreadcnt;
		break;
	case CL_WRITE:
		segcnt = mp->mnt_segwritecnt;
		maxcnt = mp->mnt_maxwritecnt;
		break;
	default:
		segcnt = min(mp->mnt_segreadcnt, mp->mnt_segwritecnt);
		maxcnt = min(mp->mnt_maxreadcnt, mp->mnt_maxwritecnt);
		break;
	}
	if (segcnt > (MAX_UPL_SIZE_BYTES >> PAGE_SHIFT)) {
	       /*
		* don't allow a size beyond the max UPL size we can create
		*/
               segcnt = MAX_UPL_SIZE_BYTES >> PAGE_SHIFT;
       }
       max_io_size = min((segcnt * PAGE_SIZE), maxcnt);

       if (max_io_size < MAX_UPL_TRANSFER_BYTES) {
	       /*
		* don't allow a size smaller than the old fixed limit
		*/
	       max_io_size = MAX_UPL_TRANSFER_BYTES;
       } else {
	       /*
		* make sure the size specified is a multiple of PAGE_SIZE
		*/
	       max_io_size &= ~PAGE_MASK;
       }
       return (max_io_size);
}