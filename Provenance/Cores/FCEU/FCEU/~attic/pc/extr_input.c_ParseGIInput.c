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
struct TYPE_3__ {scalar_t__* input; scalar_t__ inputfc; int /*<<< orphan*/  cspecial; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ FCEUGI ;

/* Variables and functions */
 int /*<<< orphan*/  Giggles (int /*<<< orphan*/ ) ; 
 scalar_t__* InputType ; 
 scalar_t__* UsrInputType ; 
 int /*<<< orphan*/  cspec ; 
 int /*<<< orphan*/  gametype ; 

void ParseGIInput(FCEUGI *gi)
{
 gametype=gi->type;
 
 InputType[0]=UsrInputType[0];
 InputType[1]=UsrInputType[1];
 InputType[2]=UsrInputType[2];
 
 if(gi->input[0]>=0)
  InputType[0]=gi->input[0];
 if(gi->input[1]>=0)
  InputType[1]=gi->input[1];
 if(gi->inputfc>=0)
  InputType[2]=gi->inputfc;
 cspec = gi->cspecial;

 #ifdef EXTGUI
 Giggles(gi->cspecial);
 #endif
}