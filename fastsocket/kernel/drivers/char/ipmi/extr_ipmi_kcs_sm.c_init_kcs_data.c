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
struct si_sm_data {int /*<<< orphan*/  obf_timeout; int /*<<< orphan*/  ibf_timeout; scalar_t__ truncated; scalar_t__ error_retries; scalar_t__ read_pos; scalar_t__ orig_write_count; scalar_t__ write_count; scalar_t__ write_pos; struct si_sm_io* io; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  IBF_RETRY_TIMEOUT ; 
 int /*<<< orphan*/  KCS_IDLE ; 
 int /*<<< orphan*/  OBF_RETRY_TIMEOUT ; 

__attribute__((used)) static unsigned int init_kcs_data(struct si_sm_data *kcs,
				  struct si_sm_io *io)
{
	kcs->state = KCS_IDLE;
	kcs->io = io;
	kcs->write_pos = 0;
	kcs->write_count = 0;
	kcs->orig_write_count = 0;
	kcs->read_pos = 0;
	kcs->error_retries = 0;
	kcs->truncated = 0;
	kcs->ibf_timeout = IBF_RETRY_TIMEOUT;
	kcs->obf_timeout = OBF_RETRY_TIMEOUT;

	/* Reserve 2 I/O bytes. */
	return 2;
}