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
struct io {TYPE_1__* client; } ;
struct bio {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  bios; } ;

/* Variables and functions */
 int /*<<< orphan*/  bio_free (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  retrieve_io_and_region_from_bio (struct bio*,struct io**,unsigned int*) ; 

__attribute__((used)) static void dm_bio_destructor(struct bio *bio)
{
	unsigned region;
	struct io *io;

	retrieve_io_and_region_from_bio(bio, &io, &region);

	bio_free(bio, io->client->bios);
}