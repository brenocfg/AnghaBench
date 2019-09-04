#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  yMax; int /*<<< orphan*/  xMax; int /*<<< orphan*/  yMin; int /*<<< orphan*/  xMin; } ;
typedef  int /*<<< orphan*/  FT_Outline ;
typedef  TYPE_1__ FT_BBox ;

/* Variables and functions */
 int /*<<< orphan*/  FT_Outline_Get_BBox (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  FT_Outline_Get_CBox (int /*<<< orphan*/ *,TYPE_1__*) ; 
 double XVAL (int /*<<< orphan*/ ) ; 
 long get_time () ; 
 int /*<<< orphan*/  printf (char*,double,double,double,double,double) ; 

__attribute__((used)) static void
  profile_outline( FT_Outline*   outline,
                   long          repeat )
  {
    FT_BBox  bbox;
    long     count;
    long     time0;

    time0 = get_time();
    for ( count = repeat; count > 0; count-- )
      FT_Outline_Get_CBox( outline, &bbox );

    time0 = get_time() - time0;
    printf( "time = %5.2f cbox = [%.2f %.2f %.2f %.2f]\n",
             ((double)time0/10000.0),
             XVAL( bbox.xMin ),
             XVAL( bbox.yMin ),
             XVAL( bbox.xMax ),
             XVAL( bbox.yMax ) );


    time0 = get_time();
    for ( count = repeat; count > 0; count-- )
      FT_Outline_Get_BBox( outline, &bbox );

    time0 = get_time() - time0;
    printf( "time = %5.2f bbox = [%.2f %.2f %.2f %.2f]\n",
             ((double)time0/10000.0),
             XVAL( bbox.xMin ),
             XVAL( bbox.yMin ),
             XVAL( bbox.xMax ),
             XVAL( bbox.yMax ) );
  }