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
typedef  int /*<<< orphan*/  qcelp_packet_rate ;

/* Variables and functions */
 int /*<<< orphan*/  I_F_Q ; 
 int /*<<< orphan*/  RATE_FULL ; 
 int /*<<< orphan*/  RATE_HALF ; 
 int /*<<< orphan*/  RATE_OCTAVE ; 
 int /*<<< orphan*/  RATE_QUARTER ; 
 int /*<<< orphan*/  SILENCE ; 

__attribute__((used)) static qcelp_packet_rate buf_size2bitrate(const int buf_size)
{
    switch (buf_size) {
    case 35: return RATE_FULL;
    case 17: return RATE_HALF;
    case  8: return RATE_QUARTER;
    case  4: return RATE_OCTAVE;
    case  1: return SILENCE;
    }

    return I_F_Q;
}