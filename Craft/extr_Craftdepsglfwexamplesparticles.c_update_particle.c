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
struct TYPE_3__ {float life; float vz; float x; float vx; float y; float vy; float z; scalar_t__ active; } ;
typedef  TYPE_1__ PARTICLE ;

/* Variables and functions */
 int FOUNTAIN_HEIGHT ; 
 int FOUNTAIN_R2 ; 
 int FRICTION ; 
 float GRAVITY ; 
 float LIFE_SPAN ; 
 int PARTICLE_SIZE ; 

__attribute__((used)) static void update_particle(PARTICLE *p, float dt)
{
    // If the particle is not active, we need not do anything
    if (!p->active)
        return;

    // The particle is getting older...
    p->life -= dt * (1.f / LIFE_SPAN);

    // Did the particle die?
    if (p->life <= 0.f)
    {
        p->active = 0;
        return;
    }

    // Apply gravity
    p->vz = p->vz - GRAVITY * dt;

    // Update particle position
    p->x = p->x + p->vx * dt;
    p->y = p->y + p->vy * dt;
    p->z = p->z + p->vz * dt;

    // Simple collision detection + response
    if (p->vz < 0.f)
    {
        // Particles should bounce on the fountain (with friction)
        if ((p->x * p->x + p->y * p->y) < FOUNTAIN_R2 &&
            p->z < (FOUNTAIN_HEIGHT + PARTICLE_SIZE / 2))
        {
            p->vz = -FRICTION * p->vz;
            p->z  = FOUNTAIN_HEIGHT + PARTICLE_SIZE / 2 +
                    FRICTION * (FOUNTAIN_HEIGHT +
                    PARTICLE_SIZE / 2 - p->z);
        }

        // Particles should bounce on the floor (with friction)
        else if (p->z < PARTICLE_SIZE / 2)
        {
            p->vz = -FRICTION * p->vz;
            p->z  = PARTICLE_SIZE / 2 +
                    FRICTION * (PARTICLE_SIZE / 2 - p->z);
        }
    }
}