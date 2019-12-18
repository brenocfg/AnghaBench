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
struct stv0297_state {int dummy; } ;
typedef  int fe_modulation_t ;

/* Variables and functions */
 int EINVAL ; 
#define  QAM_128 132 
#define  QAM_16 131 
#define  QAM_256 130 
#define  QAM_32 129 
#define  QAM_64 128 
 int /*<<< orphan*/  stv0297_writereg_mask (struct stv0297_state*,int,int,int) ; 

__attribute__((used)) static int stv0297_set_qam(struct stv0297_state *state, fe_modulation_t modulation)
{
	int val = 0;

	switch (modulation) {
	case QAM_16:
		val = 0;
		break;

	case QAM_32:
		val = 1;
		break;

	case QAM_64:
		val = 4;
		break;

	case QAM_128:
		val = 2;
		break;

	case QAM_256:
		val = 3;
		break;

	default:
		return -EINVAL;
	}

	stv0297_writereg_mask(state, 0x00, 0x70, val << 4);

	return 0;
}