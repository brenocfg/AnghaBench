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
struct dm_crypt_io {int /*<<< orphan*/  error; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  crypt_dec_pending (struct dm_crypt_io*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void kcryptd_crypt_read_done(struct dm_crypt_io *io, int error)
{
	if (unlikely(error < 0))
		io->error = -EIO;

	crypt_dec_pending(io);
}