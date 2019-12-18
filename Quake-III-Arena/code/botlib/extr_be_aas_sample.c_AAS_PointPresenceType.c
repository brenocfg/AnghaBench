#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_4__ {TYPE_1__* areasettings; int /*<<< orphan*/  loaded; } ;
struct TYPE_3__ {int presencetype; } ;

/* Variables and functions */
 int AAS_PointAreaNum (int /*<<< orphan*/ ) ; 
 int PRESENCE_NONE ; 
 TYPE_2__ aasworld ; 

int AAS_PointPresenceType(vec3_t point)
{
	int areanum;

	if (!aasworld.loaded) return 0;

	areanum = AAS_PointAreaNum(point);
	if (!areanum) return PRESENCE_NONE;
	return aasworld.areasettings[areanum].presencetype;
}