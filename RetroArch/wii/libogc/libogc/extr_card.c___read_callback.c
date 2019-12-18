#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct card_bat {size_t* fat; } ;
typedef  size_t s32 ;
typedef  int /*<<< orphan*/  (* cardcallback ) (size_t,size_t) ;
struct TYPE_6__ {int len; int offset; size_t iblock; } ;
typedef  TYPE_1__ card_file ;
struct TYPE_7__ {int sector_size; size_t blocks; int /*<<< orphan*/  (* card_api_cb ) (size_t,size_t) ;int /*<<< orphan*/  cmd_usr_buf; TYPE_1__* curr_file; } ;
typedef  TYPE_2__ card_block ;

/* Variables and functions */
 size_t CARD_ERROR_BROKEN ; 
 size_t CARD_ERROR_CANCELED ; 
 size_t CARD_SYSAREA ; 
 size_t EXI_CHANNEL_0 ; 
 size_t EXI_CHANNEL_2 ; 
 struct card_bat* __card_getbatblock (TYPE_2__*) ; 
 int /*<<< orphan*/  __card_putcntrlblock (TYPE_2__*,size_t) ; 
 scalar_t__ __card_read (size_t,int,size_t,int /*<<< orphan*/ ,void (*) (size_t,size_t)) ; 
 TYPE_2__* cardmap ; 

__attribute__((used)) static void __read_callback(s32 chn,s32 result)
{
	s32 ret;
	s32 len;
	cardcallback cb = NULL;
	card_file *file = NULL;
	card_block *card = 0;
	struct card_bat *fatblock = NULL;
	if(chn<EXI_CHANNEL_0 || chn>=EXI_CHANNEL_2) return;
	card = &cardmap[chn];

	ret = result;
	file = card->curr_file;
	if(ret>=0) {
		if(file->len>=0) {
			file->len = file->len-(((file->offset+card->sector_size)&~(card->sector_size-1))-file->offset);
			if(file->len>0) {
				fatblock = __card_getbatblock(card);
				file->offset += (((file->offset+card->sector_size)&~(card->sector_size-1))-file->offset);
				file->iblock = fatblock->fat[file->iblock-CARD_SYSAREA];
				if(file->iblock<CARD_SYSAREA || file->iblock>=card->blocks) {
					ret = CARD_ERROR_BROKEN;
					goto exit;
				}
				len = file->len<card->sector_size?card->sector_size:file->len;
				if(__card_read(chn,(file->iblock*card->sector_size),len,card->cmd_usr_buf,__read_callback)>=0) return;

			}
		} else
			ret = CARD_ERROR_CANCELED;
	}

exit:
	cb = card->card_api_cb;
	card->card_api_cb = NULL;
	__card_putcntrlblock(card,ret);
	if(cb) cb(chn,ret);
}