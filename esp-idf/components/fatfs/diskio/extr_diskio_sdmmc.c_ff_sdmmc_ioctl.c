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
struct TYPE_5__ {int /*<<< orphan*/  sector_size; int /*<<< orphan*/  capacity; } ;
struct TYPE_6__ {TYPE_1__ csd; } ;
typedef  TYPE_2__ sdmmc_card_t ;
typedef  int /*<<< orphan*/  WORD ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  DRESULT ;
typedef  size_t BYTE ;

/* Variables and functions */
#define  CTRL_SYNC 131 
#define  GET_BLOCK_SIZE 130 
#define  GET_SECTOR_COUNT 129 
#define  GET_SECTOR_SIZE 128 
 int /*<<< orphan*/  RES_ERROR ; 
 int /*<<< orphan*/  RES_OK ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 TYPE_2__** s_cards ; 

DRESULT ff_sdmmc_ioctl (BYTE pdrv, BYTE cmd, void* buff)
{
    sdmmc_card_t* card = s_cards[pdrv];
    assert(card);
    switch(cmd) {
        case CTRL_SYNC:
            return RES_OK;
        case GET_SECTOR_COUNT:
            *((DWORD*) buff) = card->csd.capacity;
            return RES_OK;
        case GET_SECTOR_SIZE:
            *((WORD*) buff) = card->csd.sector_size;
            return RES_OK;
        case GET_BLOCK_SIZE:
            return RES_ERROR;
    }
    return RES_ERROR;
}