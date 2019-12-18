#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  colfx ;
struct TYPE_10__ {int /*<<< orphan*/  control; } ;
struct TYPE_7__ {int member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_9__ {int /*<<< orphan*/  hdr; int /*<<< orphan*/  v; int /*<<< orphan*/  u; int /*<<< orphan*/  enable; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; TYPE_1__ member_0; } ;
struct TYPE_8__ {int /*<<< orphan*/  v; int /*<<< orphan*/  u; int /*<<< orphan*/  enable; } ;
typedef  TYPE_2__ MMAL_PARAM_COLOURFX_T ;
typedef  TYPE_3__ MMAL_PARAMETER_COLOURFX_T ;
typedef  TYPE_4__ MMAL_COMPONENT_T ;

/* Variables and functions */
 int /*<<< orphan*/  MMAL_PARAMETER_COLOUR_EFFECT ; 
 int /*<<< orphan*/  mmal_port_parameter_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int mmal_status_to_int (int /*<<< orphan*/ ) ; 

int raspicamcontrol_set_colourFX(MMAL_COMPONENT_T *camera, const MMAL_PARAM_COLOURFX_T *colourFX)
{
   MMAL_PARAMETER_COLOURFX_T colfx = {{MMAL_PARAMETER_COLOUR_EFFECT,sizeof(colfx)}, 0, 0, 0};

   if (!camera)
      return 1;

   colfx.enable = colourFX->enable;
   colfx.u = colourFX->u;
   colfx.v = colourFX->v;

   return mmal_status_to_int(mmal_port_parameter_set(camera->control, &colfx.hdr));

}