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
struct TYPE_6__ {int capacity; } ;
struct TYPE_7__ {TYPE_1__ csd; } ;
typedef  TYPE_2__ sdmmc_card_t ;

/* Variables and functions */
 int /*<<< orphan*/  do_single_write_read_test (TYPE_2__*,int,int,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  sdmmc_card_print_info (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void read_write_test(sdmmc_card_t* card)
{
    sdmmc_card_print_info(stdout, card);
    printf("  sector  | count | align | size(kB)  | wr_time(ms) | wr_speed(MB/s)  |  rd_time(ms)  | rd_speed(MB/s)\n");
    do_single_write_read_test(card, 0, 1, 4);
    do_single_write_read_test(card, 0, 4, 4);
    do_single_write_read_test(card, 1, 16, 4);
    do_single_write_read_test(card, 16, 32, 4);
    do_single_write_read_test(card, 48, 64, 4);
    do_single_write_read_test(card, 128, 128, 4);
    do_single_write_read_test(card, card->csd.capacity - 64, 32, 4);
    do_single_write_read_test(card, card->csd.capacity - 64, 64, 4);
    do_single_write_read_test(card, card->csd.capacity - 8, 1, 4);
    do_single_write_read_test(card, card->csd.capacity/2, 1, 4);
    do_single_write_read_test(card, card->csd.capacity/2, 4, 4);
    do_single_write_read_test(card, card->csd.capacity/2, 8, 4);
    do_single_write_read_test(card, card->csd.capacity/2, 16, 4);
    do_single_write_read_test(card, card->csd.capacity/2, 32, 4);
    do_single_write_read_test(card, card->csd.capacity/2, 64, 4);
    do_single_write_read_test(card, card->csd.capacity/2, 128, 4);
    do_single_write_read_test(card, card->csd.capacity/2, 1, 1);
    do_single_write_read_test(card, card->csd.capacity/2, 8, 1);
    do_single_write_read_test(card, card->csd.capacity/2, 128, 1);
}