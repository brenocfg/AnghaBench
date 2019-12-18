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
struct saa5246a_device {int /*<<< orphan*/  in_use; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMMAND_END ; 
 int R1_8_BITS_NO_PARITY ; 
 int R1_DAUS_ALL_OFF ; 
 int R1_DEW ; 
 int R1_EXTENDED_PACKET_DISABLE ; 
 int R1_INTERLACED_312_AND_HALF_312_AND_HALF_LINES ; 
 int R1_VCS_TO_SCS ; 
 int /*<<< orphan*/  SAA5246A_REGISTER_R1 ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_senddata (struct saa5246a_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct saa5246a_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int saa5246a_release(struct file *file)
{
	struct saa5246a_device *t = video_drvdata(file);

	/* Stop all acquisition circuits. */
	i2c_senddata(t, SAA5246A_REGISTER_R1,

		R1_INTERLACED_312_AND_HALF_312_AND_HALF_LINES |
		R1_DEW |
		R1_EXTENDED_PACKET_DISABLE |
		R1_DAUS_ALL_OFF |
		R1_8_BITS_NO_PARITY |
		R1_VCS_TO_SCS,

		COMMAND_END);
	clear_bit(0, &t->in_use);
	return 0;
}