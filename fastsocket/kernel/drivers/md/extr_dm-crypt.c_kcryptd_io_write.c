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
struct TYPE_2__ {struct bio* bio_out; } ;
struct dm_crypt_io {TYPE_1__ ctx; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  generic_make_request (struct bio*) ; 

__attribute__((used)) static void kcryptd_io_write(struct dm_crypt_io *io)
{
	struct bio *clone = io->ctx.bio_out;
	generic_make_request(clone);
}