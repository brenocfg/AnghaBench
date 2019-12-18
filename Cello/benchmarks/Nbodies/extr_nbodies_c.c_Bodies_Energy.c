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
struct Body {double mass; double vx; double vy; double vz; double x; double y; double z; } ;

/* Variables and functions */
 double sqrt (double) ; 

__attribute__((used)) static double Bodies_Energy(struct Body* bodies, size_t nbodies) {

  double dx = 0.0;
  double dy = 0.0;
  double dz = 0.0;
  double distance = 0.0;
  double e = 0.0;
  
  for(size_t i = 0; i < nbodies; i++) {
  
    struct Body* body0 = &bodies[i];

    e += (0.5 * body0->mass * (
        body0->vx * body0->vx +
        body0->vy * body0->vy +
        body0->vz * body0->vz));

    for(size_t j = i+1; j < nbodies; j++) {
      
      struct Body* body1 = &bodies[j];

      dx = body0->x - body1->x;
      dy = body0->y - body1->y;
      dz = body0->z - body1->z;

      distance = sqrt(dx * dx + dy * dy + dz * dz);
      e -= (body0->mass * body1->mass) / distance;
    }
  }
  
  return e;
}