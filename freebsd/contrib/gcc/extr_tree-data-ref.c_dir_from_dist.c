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
typedef  enum data_dependence_direction { ____Placeholder_data_dependence_direction } data_dependence_direction ;

/* Variables and functions */
 int dir_equal ; 
 int dir_negative ; 
 int dir_positive ; 

__attribute__((used)) static inline enum data_dependence_direction
dir_from_dist (int dist)
{
  if (dist > 0)
    return dir_positive;
  else if (dist < 0)
    return dir_negative;
  else
    return dir_equal;
}