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
struct si_sm_data {unsigned int read_pos; int truncated; int /*<<< orphan*/  read_data; } ;

/* Variables and functions */
 unsigned char IPMI_ERR_MSG_TRUNCATED ; 
 unsigned char IPMI_ERR_UNSPECIFIED ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int get_kcs_result(struct si_sm_data *kcs, unsigned char *data,
			  unsigned int length)
{
	if (length < kcs->read_pos) {
		kcs->read_pos = length;
		kcs->truncated = 1;
	}

	memcpy(data, kcs->read_data, kcs->read_pos);

	if ((length >= 3) && (kcs->read_pos < 3)) {
		/* Guarantee that we return at least 3 bytes, with an
		   error in the third byte if it is too short. */
		data[2] = IPMI_ERR_UNSPECIFIED;
		kcs->read_pos = 3;
	}
	if (kcs->truncated) {
		/*
		 * Report a truncated error.  We might overwrite
		 * another error, but that's too bad, the user needs
		 * to know it was truncated.
		 */
		data[2] = IPMI_ERR_MSG_TRUNCATED;
		kcs->truncated = 0;
	}

	return kcs->read_pos;
}