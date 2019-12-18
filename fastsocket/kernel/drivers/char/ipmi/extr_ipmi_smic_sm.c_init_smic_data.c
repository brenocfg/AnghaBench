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
struct si_sm_io {int dummy; } ;
struct si_sm_data {int /*<<< orphan*/  smic_timeout; scalar_t__ truncated; scalar_t__ error_retries; scalar_t__ read_pos; scalar_t__ orig_write_count; scalar_t__ write_count; scalar_t__ write_pos; struct si_sm_io* io; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMIC_IDLE ; 
 int /*<<< orphan*/  SMIC_RETRY_TIMEOUT ; 

__attribute__((used)) static unsigned int init_smic_data(struct si_sm_data *smic,
				   struct si_sm_io *io)
{
	smic->state = SMIC_IDLE;
	smic->io = io;
	smic->write_pos = 0;
	smic->write_count = 0;
	smic->orig_write_count = 0;
	smic->read_pos = 0;
	smic->error_retries = 0;
	smic->truncated = 0;
	smic->smic_timeout = SMIC_RETRY_TIMEOUT;

	/* We use 3 bytes of I/O. */
	return 3;
}