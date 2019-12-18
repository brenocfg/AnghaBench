#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rsxx_cardinfo {TYPE_1__* gendisk; } ;
struct hd_struct {int dummy; } ;
struct bio {int dummy; } ;
struct TYPE_2__ {struct hd_struct part0; } ;

/* Variables and functions */
 int bio_data_dir (struct bio*) ; 
 int /*<<< orphan*/  part_inc_in_flight (struct hd_struct*,int) ; 
 int /*<<< orphan*/  part_round_stats (int,struct hd_struct*) ; 
 int part_stat_lock () ; 
 int /*<<< orphan*/  part_stat_unlock () ; 

__attribute__((used)) static void disk_stats_start(struct rsxx_cardinfo *card, struct bio *bio)
{
	struct hd_struct *part0 = &card->gendisk->part0;
	int rw = bio_data_dir(bio);
	int cpu;

	cpu = part_stat_lock();

	part_round_stats(cpu, part0);
	part_inc_in_flight(part0, rw);

	part_stat_unlock();
}