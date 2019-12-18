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
typedef  int uint8_t ;
struct comedi_cmd {int chanlist_len; int /*<<< orphan*/ * chanlist; } ;

/* Variables and functions */
 int CR_CHAN (int /*<<< orphan*/ ) ; 
 scalar_t__ CR_RANGE (int /*<<< orphan*/ ) ; 
 int EOPL ; 
 int RANGE_10V ; 
 int RANGE_5V ; 

__attribute__((used)) static int s626_ai_load_polllist(uint8_t * ppl, struct comedi_cmd *cmd)
{

	int n;

	for (n = 0; n < cmd->chanlist_len; n++) {
		if (CR_RANGE((cmd->chanlist)[n]) == 0)
			ppl[n] = (CR_CHAN((cmd->chanlist)[n])) | (RANGE_5V);
		else
			ppl[n] = (CR_CHAN((cmd->chanlist)[n])) | (RANGE_10V);
	}
	if (n != 0)
		ppl[n - 1] |= EOPL;

	return n;
}