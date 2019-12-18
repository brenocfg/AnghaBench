#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int profile; int pns; int encoder_version; int /*<<< orphan*/  profile_name; } ;
typedef  TYPE_1__ mpc_streaminfo ;
typedef  int /*<<< orphan*/  mpc_bits_reader ;

/* Variables and functions */
 int mpc_bits_read (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mpc_get_encoder_string (TYPE_1__*) ; 
 int /*<<< orphan*/  mpc_get_version_string (int) ; 

void  streaminfo_encoder_info(mpc_streaminfo* si, const mpc_bits_reader * r_in)
{
	mpc_bits_reader r = *r_in;

	si->profile            = mpc_bits_read(&r, 7) / 8.;
	si->profile_name       = mpc_get_version_string(si->profile);
	si->pns                = mpc_bits_read(&r, 1);
	si->encoder_version = mpc_bits_read(&r, 8) << 24; // major
	si->encoder_version |= mpc_bits_read(&r, 8) << 16; // minor
	si->encoder_version |= mpc_bits_read(&r, 8) << 8; // build


	mpc_get_encoder_string(si);
}