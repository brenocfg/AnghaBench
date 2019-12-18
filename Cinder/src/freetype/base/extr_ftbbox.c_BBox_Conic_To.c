#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  yMax; int /*<<< orphan*/  yMin; int /*<<< orphan*/  xMax; int /*<<< orphan*/  xMin; } ;
struct TYPE_13__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_12__ {TYPE_2__ last; TYPE_4__ bbox; } ;
typedef  TYPE_1__ TBBox_Rec ;
typedef  TYPE_2__ FT_Vector ;

/* Variables and functions */
 int /*<<< orphan*/  BBox_Conic_Check (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ CHECK_X (TYPE_2__*,TYPE_4__) ; 
 scalar_t__ CHECK_Y (TYPE_2__*,TYPE_4__) ; 
 int /*<<< orphan*/  FT_UPDATE_BBOX (TYPE_2__*,TYPE_4__) ; 

__attribute__((used)) static int
  BBox_Conic_To( FT_Vector*  control,
                 FT_Vector*  to,
                 TBBox_Rec*  user )
  {
    /* in case `to' is implicit and not included in bbox yet */
    FT_UPDATE_BBOX( to, user->bbox );

    if ( CHECK_X( control, user->bbox ) )
      BBox_Conic_Check( user->last.x,
                        control->x,
                        to->x,
                        &user->bbox.xMin,
                        &user->bbox.xMax );

    if ( CHECK_Y( control, user->bbox ) )
      BBox_Conic_Check( user->last.y,
                        control->y,
                        to->y,
                        &user->bbox.yMin,
                        &user->bbox.yMax );

    user->last = *to;

    return 0;
  }