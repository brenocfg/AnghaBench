#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int /*<<< orphan*/  s32 ;
typedef  int /*<<< orphan*/ * cardcallback ;
struct TYPE_7__ {int offset; int iblock; int /*<<< orphan*/  chn; } ;
typedef  TYPE_1__ card_file ;
struct TYPE_8__ {int sector_size; int /*<<< orphan*/ * card_api_cb; } ;
typedef  TYPE_2__ card_block ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_ERROR_FATAL_ERROR ; 
 int /*<<< orphan*/  DCInvalidateRange (void*,int) ; 
 int /*<<< orphan*/ * __card_defaultapicallback ; 
 int /*<<< orphan*/  __card_putcntrlblock (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __card_read (int /*<<< orphan*/ ,int,int,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __card_seek (TYPE_1__*,int,int,TYPE_2__**) ; 
 int /*<<< orphan*/  __read_callback ; 

s32 CARD_ReadAsync(card_file *file,void *buffer,u32 len,u32 offset,cardcallback callback)
{
	s32 ret;
	cardcallback cb = NULL;
	card_block *card = NULL;

	if(len<=0 || (len&0x1ff) || (offset>0 && (offset&0x1ff))) return CARD_ERROR_FATAL_ERROR;
	if((ret=__card_seek(file,len,offset,&card))<0) return ret;

	DCInvalidateRange(buffer,len);

	cb = callback;
	if(!cb) cb = __card_defaultapicallback;
	card->card_api_cb = cb;

	if(len>=(card->sector_size-(file->offset&(card->sector_size-1)))) len = (card->sector_size-(file->offset&(card->sector_size-1)));

	if((ret=__card_read(file->chn,(file->iblock*card->sector_size),len,buffer,__read_callback))<0) {
		__card_putcntrlblock(card,ret);
		return ret;
	}
	return 0;
}