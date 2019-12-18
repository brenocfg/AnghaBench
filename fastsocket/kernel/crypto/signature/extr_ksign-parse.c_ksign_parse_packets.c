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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  ksign_user_id_actor_t ;
typedef  int /*<<< orphan*/  ksign_signature_actor_t ;
typedef  int /*<<< orphan*/  ksign_public_key_actor_t ;

/* Variables and functions */
 int ksign_parse_one_packet (int /*<<< orphan*/  const**,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

int ksign_parse_packets(const uint8_t *buf,
			size_t size,
			ksign_signature_actor_t sigfnx,
			ksign_public_key_actor_t pkfnx,
			ksign_user_id_actor_t uidfnx,
			void *data)
{
	const uint8_t *datap, *endp;
	int rc;

	datap = buf;
	endp = buf + size;
	do {
		rc = ksign_parse_one_packet(&datap, endp,
					    sigfnx, pkfnx, uidfnx, data);
	} while (rc == 0 && datap < endp);

	return rc;
}