#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  blip_t ;
struct TYPE_2__ {int** PreAmp; int /*<<< orphan*/  SRWidth; int /*<<< orphan*/  NoiseFeedback; } ;

/* Variables and functions */
 int /*<<< orphan*/  FB_DISCRETE ; 
 int /*<<< orphan*/  FB_SEGAVDP ; 
 TYPE_1__ SN76489 ; 
 int SN_DISCRETE ; 
 int /*<<< orphan*/  SRW_DISCRETE ; 
 int /*<<< orphan*/  SRW_SEGAVDP ; 
 int /*<<< orphan*/ ** blip ; 

void SN76489_Init(blip_t* left, blip_t* right, int type)
{
  int i;
  
  blip[0] = left;
  blip[1] = right;

  for (i=0; i<4; i++)
  {
    SN76489.PreAmp[i][0] = 100;
    SN76489.PreAmp[i][1] = 100;
  }

  if (type == SN_DISCRETE)
  {
    SN76489.NoiseFeedback = FB_DISCRETE;
    SN76489.SRWidth = SRW_DISCRETE;
  }
  else
  {
    SN76489.NoiseFeedback = FB_SEGAVDP;
    SN76489.SRWidth = SRW_SEGAVDP;
  }
}