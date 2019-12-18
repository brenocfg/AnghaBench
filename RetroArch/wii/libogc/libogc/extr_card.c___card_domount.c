#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_5__ {int** flash_id; int* flashID_chksum; } ;
typedef  TYPE_1__ syssramex ;
typedef  size_t s32 ;
struct TYPE_6__ {int mount_step; int cid; int card_size; int sector_size; int blocks; scalar_t__ workarea; scalar_t__ key; int /*<<< orphan*/  latency; } ;
typedef  TYPE_2__ card_block ;

/* Variables and functions */
 size_t CARD_ERROR_IOERROR ; 
 size_t CARD_ERROR_NOCARD ; 
 size_t CARD_ERROR_READY ; 
 size_t CARD_ERROR_WRONGDEVICE ; 
 int CARD_STATUS_UNLOCKED ; 
 int /*<<< orphan*/  DCInvalidateRange (scalar_t__,int) ; 
 size_t EXI_CHANNEL_0 ; 
 size_t EXI_CHANNEL_2 ; 
 int /*<<< orphan*/  EXI_DEVICE_0 ; 
 scalar_t__ EXI_GetID (size_t,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ EXI_Probe (size_t) ; 
 int /*<<< orphan*/  EXI_RegisterEXICallback (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXI_Unlock (size_t) ; 
 int _ROTL (int,int) ; 
 TYPE_1__* __SYS_LockSramEx () ; 
 int /*<<< orphan*/  __SYS_UnlockSramEx (int) ; 
 size_t __card_clearstatus (size_t) ; 
 int /*<<< orphan*/  __card_dounmount (size_t,size_t) ; 
 size_t __card_enableinterrupt (size_t,int) ; 
 int /*<<< orphan*/  __card_exihandler ; 
 int /*<<< orphan*/  __card_iscard (int) ; 
 int /*<<< orphan*/  __card_mountcallback ; 
 size_t __card_read (size_t,int,int,scalar_t__,int /*<<< orphan*/ ) ; 
 size_t __card_readstatus (size_t,int*) ; 
 size_t __dounlock (size_t,scalar_t__) ; 
 int /*<<< orphan*/ * card_latency ; 
 int* card_sector_size ; 
 TYPE_2__* cardmap ; 

__attribute__((used)) static s32 __card_domount(s32 chn)
{
	u8 status,kval;
	s32 ret = CARD_ERROR_READY;
	u32 sum;
	u32 id,idx,cnt;
	card_block *card;
	syssramex *sramex;

	if(chn<EXI_CHANNEL_0 || chn>=EXI_CHANNEL_2) return CARD_ERROR_NOCARD;
	card = &cardmap[chn];
	if(card->mount_step==0) {
		ret = 0;
		id = 0;
		if(EXI_GetID(chn,EXI_DEVICE_0,&id)==0) ret = CARD_ERROR_NOCARD;
		else if(!__card_iscard(id)) ret = CARD_ERROR_WRONGDEVICE;

		if(ret<0) goto exit;
		card->cid = id;
		card->card_size = (id&0xfc);
		if(card->card_size) {
			idx = _ROTL(id,23)&0x1c;
			card->sector_size = card_sector_size[idx>>2];
			card->blocks = ((card->card_size<<20)>>3)/card->sector_size;

			if(card->blocks>0x0008) {
				idx = _ROTL(id,26)&0x1c;
				card->latency = card_latency[idx>>2];

				if((ret=__card_clearstatus(chn))<0) goto exit;
				if((ret=__card_readstatus(chn,&status))<0) goto exit;

				if(EXI_Probe(chn)==0) {
					ret = CARD_ERROR_NOCARD;
					goto exit;
				}
				if(!(status&CARD_STATUS_UNLOCKED)) {
					if((ret=__dounlock(chn,card->key))<0) goto exit;

					cnt = 0;
					sum = 0;
					sramex = __SYS_LockSramEx();
					while(cnt<12) {
						kval = ((u8*)card->key)[cnt];
						sramex->flash_id[chn][cnt] = kval;
						sum += kval;
						cnt++;
					}
					sum = (sum^-1)&0xff;
					sramex->flashID_chksum[chn] = (sum<<8)|sum;
					__SYS_UnlockSramEx(1);
					return ret;
				}
				card->mount_step = 1;

				cnt = 0;
				sum = 0;
				sramex = __SYS_LockSramEx();
				while(cnt<12) {
					sum += sramex->flash_id[chn][cnt];
					cnt++;
				}
				cnt = sramex->flashID_chksum[chn];
				__SYS_UnlockSramEx(0);

				sum = (sum^-1)&0xff;
				sum |= (sum<<8);
				if(cnt!=sum) {
					ret = CARD_ERROR_IOERROR;
					goto exit;
				}
			}
		}
	}
	if(card->mount_step==1) {
		card->mount_step = 2;
		if((ret=__card_enableinterrupt(chn,1))<0) goto exit;
		EXI_RegisterEXICallback(chn,__card_exihandler);
		EXI_Unlock(chn);

		DCInvalidateRange(card->workarea,0xA000);
	}

	if((ret=__card_read(chn,(card->sector_size*(card->mount_step-2)),card->sector_size,card->workarea+((card->mount_step-2)<<13),__card_mountcallback))<0) goto exit;
	return ret;

exit:
	EXI_Unlock(chn);
	__card_dounmount(chn,ret);

	return ret;
}