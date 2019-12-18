#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tid_t ;
struct tlock {int /*<<< orphan*/  lock; } ;
struct pxd_lock {int index; int /*<<< orphan*/  pxd; int /*<<< orphan*/  flag; } ;
struct inode {int dummy; } ;
struct TYPE_6__ {int flag; } ;
typedef  TYPE_1__ dxd_t ;

/* Variables and functions */
 int /*<<< orphan*/  COMMIT_Inlineea ; 
 int /*<<< orphan*/  COMMIT_Nolink ; 
 int DXD_EXTENT ; 
 int DXD_INLINE ; 
 int /*<<< orphan*/  PXDaddress (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PXDlength (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addressDXD (TYPE_1__*) ; 
 int /*<<< orphan*/  lengthDXD (TYPE_1__*) ; 
 int /*<<< orphan*/  mlckALLOCPXD ; 
 int /*<<< orphan*/  mlckFREEPXD ; 
 int /*<<< orphan*/  set_cflag (int /*<<< orphan*/ ,struct inode*) ; 
 int /*<<< orphan*/  test_cflag (int /*<<< orphan*/ ,struct inode*) ; 
 int /*<<< orphan*/  tlckMAP ; 
 struct tlock* txMaplock (int /*<<< orphan*/ ,struct inode*,int /*<<< orphan*/ ) ; 

void txEA(tid_t tid, struct inode *ip, dxd_t * oldea, dxd_t * newea)
{
	struct tlock *tlck = NULL;
	struct pxd_lock *maplock = NULL, *pxdlock = NULL;

	/*
	 * format maplock for alloc of new EA extent
	 */
	if (newea) {
		/* Since the newea could be a completely zeroed entry we need to
		 * check for the two flags which indicate we should actually
		 * commit new EA data
		 */
		if (newea->flag & DXD_EXTENT) {
			tlck = txMaplock(tid, ip, tlckMAP);
			maplock = (struct pxd_lock *) & tlck->lock;
			pxdlock = (struct pxd_lock *) maplock;
			pxdlock->flag = mlckALLOCPXD;
			PXDaddress(&pxdlock->pxd, addressDXD(newea));
			PXDlength(&pxdlock->pxd, lengthDXD(newea));
			pxdlock++;
			maplock->index = 1;
		} else if (newea->flag & DXD_INLINE) {
			tlck = NULL;

			set_cflag(COMMIT_Inlineea, ip);
		}
	}

	/*
	 * format maplock for free of old EA extent
	 */
	if (!test_cflag(COMMIT_Nolink, ip) && oldea->flag & DXD_EXTENT) {
		if (tlck == NULL) {
			tlck = txMaplock(tid, ip, tlckMAP);
			maplock = (struct pxd_lock *) & tlck->lock;
			pxdlock = (struct pxd_lock *) maplock;
			maplock->index = 0;
		}
		pxdlock->flag = mlckFREEPXD;
		PXDaddress(&pxdlock->pxd, addressDXD(oldea));
		PXDlength(&pxdlock->pxd, lengthDXD(oldea));
		maplock->index++;
	}
}