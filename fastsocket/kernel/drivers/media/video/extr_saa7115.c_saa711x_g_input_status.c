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
typedef  scalar_t__ u32 ;
struct v4l2_subdev {int dummy; } ;
struct saa711x_state {scalar_t__ ident; } ;

/* Variables and functions */
 int /*<<< orphan*/  R_1E_STATUS_BYTE_1_VD_DEC ; 
 int /*<<< orphan*/  R_1F_STATUS_BYTE_2_VD_DEC ; 
 scalar_t__ V4L2_IDENT_SAA7115 ; 
 scalar_t__ V4L2_IN_ST_NO_SIGNAL ; 
 int saa711x_read (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 struct saa711x_state* to_state (struct v4l2_subdev*) ; 

__attribute__((used)) static int saa711x_g_input_status(struct v4l2_subdev *sd, u32 *status)
{
	struct saa711x_state *state = to_state(sd);
	int reg1e = 0x80;
	int reg1f;

	*status = V4L2_IN_ST_NO_SIGNAL;
	if (state->ident == V4L2_IDENT_SAA7115)
		reg1e = saa711x_read(sd, R_1E_STATUS_BYTE_1_VD_DEC);
	reg1f = saa711x_read(sd, R_1F_STATUS_BYTE_2_VD_DEC);
	if ((reg1f & 0xc1) == 0x81 && (reg1e & 0xc0) == 0x80)
		*status = 0;
	return 0;
}