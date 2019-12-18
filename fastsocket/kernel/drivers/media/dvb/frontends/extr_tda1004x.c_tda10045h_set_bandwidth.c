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
typedef  int u8 ;
struct tda1004x_state {int dummy; } ;
typedef  int fe_bandwidth_t ;
typedef  int /*<<< orphan*/  bandwidth_8mhz ;
typedef  int /*<<< orphan*/  bandwidth_7mhz ;
typedef  int /*<<< orphan*/  bandwidth_6mhz ;

/* Variables and functions */
#define  BANDWIDTH_6_MHZ 130 
#define  BANDWIDTH_7_MHZ 129 
#define  BANDWIDTH_8_MHZ 128 
 int EINVAL ; 
 int /*<<< orphan*/  TDA10045H_CONFPLL_P ; 
 int /*<<< orphan*/  TDA10045H_IOFFSET ; 
 int /*<<< orphan*/  tda1004x_write_buf (struct tda1004x_state*,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  tda1004x_write_byteI (struct tda1004x_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tda10045h_set_bandwidth(struct tda1004x_state *state,
				   fe_bandwidth_t bandwidth)
{
	static u8 bandwidth_6mhz[] = { 0x02, 0x00, 0x3d, 0x00, 0x60, 0x1e, 0xa7, 0x45, 0x4f };
	static u8 bandwidth_7mhz[] = { 0x02, 0x00, 0x37, 0x00, 0x4a, 0x2f, 0x6d, 0x76, 0xdb };
	static u8 bandwidth_8mhz[] = { 0x02, 0x00, 0x3d, 0x00, 0x48, 0x17, 0x89, 0xc7, 0x14 };

	switch (bandwidth) {
	case BANDWIDTH_6_MHZ:
		tda1004x_write_buf(state, TDA10045H_CONFPLL_P, bandwidth_6mhz, sizeof(bandwidth_6mhz));
		break;

	case BANDWIDTH_7_MHZ:
		tda1004x_write_buf(state, TDA10045H_CONFPLL_P, bandwidth_7mhz, sizeof(bandwidth_7mhz));
		break;

	case BANDWIDTH_8_MHZ:
		tda1004x_write_buf(state, TDA10045H_CONFPLL_P, bandwidth_8mhz, sizeof(bandwidth_8mhz));
		break;

	default:
		return -EINVAL;
	}

	tda1004x_write_byteI(state, TDA10045H_IOFFSET, 0);

	return 0;
}