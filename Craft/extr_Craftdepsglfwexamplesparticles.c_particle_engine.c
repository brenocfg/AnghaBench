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
struct TYPE_4__ {int /*<<< orphan*/  active; } ;

/* Variables and functions */
 float BIRTH_INTERVAL ; 
 int MAX_PARTICLES ; 
 float MIN_DELTA_T ; 
 int /*<<< orphan*/  init_particle (TYPE_1__*,double) ; 
 float min_age ; 
 TYPE_1__* particles ; 
 int /*<<< orphan*/  update_particle (TYPE_1__*,float) ; 

__attribute__((used)) static void particle_engine(double t, float dt)
{
    int i;
    float dt2;

    // Update particles (iterated several times per frame if dt is too large)
    while (dt > 0.f)
    {
        // Calculate delta time for this iteration
        dt2 = dt < MIN_DELTA_T ? dt : MIN_DELTA_T;

        for (i = 0;  i < MAX_PARTICLES;  i++)
            update_particle(&particles[i], dt2);

        min_age += dt2;

        // Should we create any new particle(s)?
        while (min_age >= BIRTH_INTERVAL)
        {
            min_age -= BIRTH_INTERVAL;

            // Find a dead particle to replace with a new one
            for (i = 0;  i < MAX_PARTICLES;  i++)
            {
                if (!particles[i].active)
                {
                    init_particle(&particles[i], t + min_age);
                    update_particle(&particles[i], min_age);
                    break;
                }
            }
        }

        dt -= dt2;
    }
}