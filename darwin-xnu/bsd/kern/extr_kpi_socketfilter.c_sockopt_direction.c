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
typedef  TYPE_1__* sockopt_t ;
typedef  int /*<<< orphan*/  sockopt_dir ;
struct TYPE_3__ {scalar_t__ sopt_dir; } ;

/* Variables and functions */
 scalar_t__ SOPT_GET ; 
 int /*<<< orphan*/  sockopt_get ; 
 int /*<<< orphan*/  sockopt_set ; 

sockopt_dir
sockopt_direction(sockopt_t sopt)
{
	return ((sopt->sopt_dir == SOPT_GET) ? sockopt_get : sockopt_set);
}