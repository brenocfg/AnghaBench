#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mirror_set {int dummy; } ;
struct bio_list {int dummy; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE ; 
 struct bio* bio_list_pop (struct bio_list*) ; 
 int /*<<< orphan*/  queue_bio (struct mirror_set*,struct bio*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dispatch_bios(void *context, struct bio_list *bio_list)
{
	struct mirror_set *ms = context;
	struct bio *bio;

	while ((bio = bio_list_pop(bio_list)))
		queue_bio(ms, bio, WRITE);
}