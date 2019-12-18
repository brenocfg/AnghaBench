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
struct Body {double vx; double vy; double vz; } ;

/* Variables and functions */
 double solar_mass ; 

__attribute__((used)) static void Body_Offset_Momentum(struct Body* self, double px, double py, double pz) {
  self->vx = -px / solar_mass;
  self->vy = -py / solar_mass;
  self->vz = -pz / solar_mass;
}