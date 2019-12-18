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
struct TYPE_3__ {int* in_cubemap_face_order; float* input_mirror_modifier; int /*<<< orphan*/ * in_cubemap_face_rotation; } ;
typedef  TYPE_1__ V360Context ;

/* Variables and functions */
#define  BACK 133 
#define  DOWN 132 
#define  FRONT 131 
#define  LEFT 130 
 float const M_PI ; 
 float const M_PI_2 ; 
 float const M_PI_4 ; 
#define  RIGHT 129 
#define  UP 128 
 float asinf (float const) ; 
 float atan2f (float const,float const) ; 
 float atanf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_assert0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cosf (float) ; 
 int /*<<< orphan*/  rotate_cube_face (float*,float*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xyz_to_cube(const V360Context *s,
                        const float *vec,
                        float *uf, float *vf, int *direction)
{
    const float phi   = atan2f(vec[0], -vec[2]);
    const float theta = asinf(-vec[1]);
    float phi_norm, theta_threshold;
    int face;

    if (phi >= -M_PI_4 && phi < M_PI_4) {
        *direction = FRONT;
        phi_norm = phi;
    } else if (phi >= -(M_PI_2 + M_PI_4) && phi < -M_PI_4) {
        *direction = LEFT;
        phi_norm = phi + M_PI_2;
    } else if (phi >= M_PI_4 && phi < M_PI_2 + M_PI_4) {
        *direction = RIGHT;
        phi_norm = phi - M_PI_2;
    } else {
        *direction = BACK;
        phi_norm = phi + ((phi > 0.f) ? -M_PI : M_PI);
    }

    theta_threshold = atanf(cosf(phi_norm));
    if (theta > theta_threshold) {
        *direction = DOWN;
    } else if (theta < -theta_threshold) {
        *direction = UP;
    }

    switch (*direction) {
    case RIGHT:
        *uf =  vec[2] / vec[0];
        *vf = -vec[1] / vec[0];
        break;
    case LEFT:
        *uf =  vec[2] / vec[0];
        *vf =  vec[1] / vec[0];
        break;
    case UP:
        *uf =  vec[0] / vec[1];
        *vf = -vec[2] / vec[1];
        break;
    case DOWN:
        *uf = -vec[0] / vec[1];
        *vf = -vec[2] / vec[1];
        break;
    case FRONT:
        *uf = -vec[0] / vec[2];
        *vf =  vec[1] / vec[2];
        break;
    case BACK:
        *uf = -vec[0] / vec[2];
        *vf = -vec[1] / vec[2];
        break;
    default:
        av_assert0(0);
    }

    face = s->in_cubemap_face_order[*direction];
    rotate_cube_face(uf, vf, s->in_cubemap_face_rotation[face]);

    (*uf) *= s->input_mirror_modifier[0];
    (*vf) *= s->input_mirror_modifier[1];
}