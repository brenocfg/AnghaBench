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
typedef  int /*<<< orphan*/  u32 ;
struct dvb_frontend {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TUNER_STATUS_LOCKED ; 
 int /*<<< orphan*/  TUNER_STATUS_STEREO ; 
 scalar_t__ tea5767_read_status (struct dvb_frontend*,unsigned char*) ; 
 scalar_t__ tea5767_signal (struct dvb_frontend*,unsigned char*) ; 
 scalar_t__ tea5767_stereo (struct dvb_frontend*,unsigned char*) ; 

__attribute__((used)) static int tea5767_get_status(struct dvb_frontend *fe, u32 *status)
{
	unsigned char buffer[5];

	*status = 0;

	if (0 == tea5767_read_status(fe, buffer)) {
		if (tea5767_signal(fe, buffer))
			*status = TUNER_STATUS_LOCKED;
		if (tea5767_stereo(fe, buffer))
			*status |= TUNER_STATUS_STEREO;
	}

	return 0;
}