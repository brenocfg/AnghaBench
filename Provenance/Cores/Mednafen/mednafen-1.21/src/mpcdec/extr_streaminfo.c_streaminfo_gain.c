#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* mpc_uint16_t ;
struct TYPE_3__ {void* peak_album; void* gain_album; void* peak_title; void* gain_title; } ;
typedef  TYPE_1__ mpc_streaminfo ;
typedef  int /*<<< orphan*/  mpc_bits_reader ;

/* Variables and functions */
 int mpc_bits_read (int /*<<< orphan*/ *,int) ; 

void  streaminfo_gain(mpc_streaminfo* si, const mpc_bits_reader * r_in)
{
	mpc_bits_reader r = *r_in;

	int version = mpc_bits_read(&r, 8); // gain version
	if (version != 1) // we only know ver 1
		return;
	si->gain_title         = (mpc_uint16_t) mpc_bits_read(&r, 16);
	si->peak_title         = (mpc_uint16_t) mpc_bits_read(&r, 16);
	si->gain_album         = (mpc_uint16_t) mpc_bits_read(&r, 16);
	si->peak_album         = (mpc_uint16_t) mpc_bits_read(&r, 16);
}