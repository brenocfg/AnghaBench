#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int s32 ;
struct TYPE_14__ {int state; int txdsize; int currtxsize; scalar_t__ len; int /*<<< orphan*/  (* cb ) (int,TYPE_1__*) ;int /*<<< orphan*/  offset; } ;
typedef  TYPE_1__ dvdcmdblk ;

/* Variables and functions */
 int DVD_CHIPPRESENT ; 
 int DVD_DISKIDSIZE ; 
 int /*<<< orphan*/  DVD_LowAudioStream (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,void (*) (int)) ; 
 scalar_t__ __dvd_autofinishing ; 
 int /*<<< orphan*/  __dvd_cancelcallback (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ __dvd_canceling ; 
 scalar_t__ __dvd_checkcancel (int) ; 
 int __dvd_currcmd ; 
 int __dvd_drivestate ; 
 TYPE_1__ __dvd_dummycmdblk ; 
 TYPE_1__* __dvd_executing ; 
 scalar_t__ __dvd_internalretries ; 
 int __dvd_resetrequired ; 
 int /*<<< orphan*/  __dvd_statebusy (TYPE_1__*) ; 
 int /*<<< orphan*/  __dvd_stateerror (int) ; 
 int /*<<< orphan*/  __dvd_stategettingerror () ; 
 int /*<<< orphan*/  __dvd_statemotorstopped () ; 
 int /*<<< orphan*/  __dvd_stateready () ; 
 int /*<<< orphan*/  __dvd_statetimeout () ; 
 int* _diReg ; 
 int /*<<< orphan*/  stub1 (int,TYPE_1__*) ; 
 int /*<<< orphan*/  stub2 (int,TYPE_1__*) ; 
 int /*<<< orphan*/  stub3 (int,TYPE_1__*) ; 
 int /*<<< orphan*/  stub4 (int,TYPE_1__*) ; 
 int /*<<< orphan*/  stub5 (int,TYPE_1__*) ; 
 int /*<<< orphan*/  stub6 (int,TYPE_1__*) ; 
 int /*<<< orphan*/  stub7 (int,TYPE_1__*) ; 
 int /*<<< orphan*/  stub8 (int,TYPE_1__*) ; 

__attribute__((used)) static void __dvd_statebusycb(s32 result)
{
	u32 val;
	dvdcmdblk *block;
	if(result==0x0010) {
		__dvd_executing->state = -1;
		__dvd_statetimeout();
		return;
	}
	if(__dvd_currcmd==0x0003 || __dvd_currcmd==0x000f) {
		if(result&0x0002) {
			__dvd_executing->state = -1;
			__dvd_stateerror(0x01234567);
			return;
		}
		if(result==0x0001) {
			__dvd_internalretries = 0;
			if(__dvd_currcmd==0x000f) __dvd_resetrequired = 1;
			if(__dvd_checkcancel(7)) return;

			__dvd_executing->state = 7;
			__dvd_statemotorstopped();
			return;
		}
	}
	if(result&0x0004) {

	}
	if(__dvd_currcmd==0x0001 || __dvd_currcmd==0x0004
		|| __dvd_currcmd==0x0005 || __dvd_currcmd==0x000e) {
		__dvd_executing->txdsize += (__dvd_executing->currtxsize-_diReg[6]);
	}
	if(result&0x0008) {
		__dvd_canceling = 0;
		block = __dvd_executing;
		__dvd_executing = &__dvd_dummycmdblk;
		__dvd_executing->state = 10;
		if(block->cb) block->cb(-3,block);
		if(__dvd_cancelcallback) __dvd_cancelcallback(0,block);
		__dvd_stateready();
		return;
	}
	if(result&0x0001) {
		__dvd_internalretries = 0;
		if(__dvd_checkcancel(0)) return;

		if(__dvd_currcmd==0x0001 || __dvd_currcmd==0x0004
			|| __dvd_currcmd==0x0005 || __dvd_currcmd==0x000e) {
			if(__dvd_executing->txdsize!=__dvd_executing->len) {
				__dvd_statebusy(__dvd_executing);
				return;
			}
			block = __dvd_executing;
			__dvd_executing = &__dvd_dummycmdblk;
			block->state = 0;
			if(block->cb) block->cb(block->txdsize,block);
			__dvd_stateready();
			return;
		}
		if(__dvd_currcmd==0x0009 || __dvd_currcmd==0x000a
			|| __dvd_currcmd==0x000b || __dvd_currcmd==0x000c) {

			val = _diReg[8];
			if(__dvd_currcmd==0x000a || __dvd_currcmd==0x000b) val <<= 2;

			block = __dvd_executing;
			__dvd_executing = &__dvd_dummycmdblk;
			block->state = 0;
			if(block->cb) block->cb(val,block);
			__dvd_stateready();
			return;
		}
		if(__dvd_currcmd==0x0006) {
			if(!__dvd_executing->currtxsize) {
				if(_diReg[8]&0x0001) {
					block = __dvd_executing;
					__dvd_executing = &__dvd_dummycmdblk;
					block->state = 9;
					if(block->cb) block->cb(-2,block);
					__dvd_stateready();
					return;
				}
				__dvd_autofinishing = 0;
				__dvd_executing->currtxsize = 1;
				DVD_LowAudioStream(0,__dvd_executing->len,__dvd_executing->offset,__dvd_statebusycb);
				return;
			}

			block = __dvd_executing;
			__dvd_executing = &__dvd_dummycmdblk;
			block->state = 0;
			if(block->cb) block->cb(0,block);
			__dvd_stateready();
			return;
		}
		if(__dvd_currcmd==0x0010) {
			if(__dvd_drivestate&DVD_CHIPPRESENT) {
				block = __dvd_executing;
				__dvd_executing = &__dvd_dummycmdblk;
				block->state = 0;
				if(block->cb) block->cb(DVD_DISKIDSIZE,block);
				__dvd_stateready();
				return;
			}
		}

		block = __dvd_executing;
		__dvd_executing = &__dvd_dummycmdblk;
		block->state = 0;
		if(block->cb) block->cb(0,block);
		__dvd_stateready();
		return;
	}
	if(result==0x0002) {
		if(__dvd_currcmd==0x000e) {
			__dvd_executing->state = -1;
			__dvd_stateerror(0x01234567);
			return;
		}
		if((__dvd_currcmd==0x0001 || __dvd_currcmd==0x0004
			|| __dvd_currcmd==0x0005 || __dvd_currcmd==0x000e)
			&& __dvd_executing->txdsize==__dvd_executing->len) {
				if(__dvd_checkcancel(0)) return;

				block = __dvd_executing;
				__dvd_executing = &__dvd_dummycmdblk;
				block->state = 0;
				if(block->cb) block->cb(block->txdsize,block);
				__dvd_stateready();
				return;
		}
	}
	__dvd_stategettingerror();
}