#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct card_direntry {int* gamecode; int* company; scalar_t__ filename; } ;
struct card_dat {struct card_direntry* entries; } ;
typedef  size_t s32 ;
struct TYPE_4__ {int /*<<< orphan*/  attached; } ;
typedef  TYPE_1__ card_block ;

/* Variables and functions */
 size_t CARD_ERROR_NOCARD ; 
 size_t CARD_ERROR_NOFILE ; 
 size_t CARD_ERROR_READY ; 
 size_t CARD_MAXFILES ; 
 struct card_dat* __card_getdirblock (TYPE_1__*) ; 
 scalar_t__ memcmp (int*,char const*,int) ; 
 scalar_t__ strcmp (char const*,char const*) ; 

__attribute__((used)) static s32 __card_getfilenum(card_block *card,const char *filename,const char *gamecode,const char *company,s32 *fileno)
{
	u32 i = 0;
	struct card_direntry *entries = NULL;
	struct card_dat *dirblock = NULL;
	if(!card->attached) return CARD_ERROR_NOCARD;
	dirblock = __card_getdirblock(card);

	entries = dirblock->entries;
	for(i=0;i<CARD_MAXFILES;i++) {
		if(entries[i].gamecode[0]!=0xff) {
			if(strcmp(filename,(const char*)entries[i].filename)==0) {
				if((gamecode && gamecode[0]!=0xff && memcmp(entries[i].gamecode,gamecode,4)!=0)
					|| (company && company[0]!=0xff && memcmp(entries[i].company,company,2)!=0)) continue;

				*fileno = i;
				break;
			}
		}
	}
	if(i>=CARD_MAXFILES) return CARD_ERROR_NOFILE;
	return CARD_ERROR_READY;
}