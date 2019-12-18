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
struct TYPE_3__ {int* out_cubemap_direction_order; int /*<<< orphan*/ * out_cubemap_face_rotation; } ;
typedef  TYPE_1__ V360Context ;

/* Variables and functions */
#define  BACK 133 
#define  DOWN 132 
#define  FRONT 131 
#define  LEFT 130 
#define  RIGHT 129 
#define  UP 128 
 int /*<<< orphan*/  av_assert0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  normalize_vector (float*) ; 
 int /*<<< orphan*/  rotate_cube_face_inverse (float*,float*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cube_to_xyz(const V360Context *s,
                        float uf, float vf, int face,
                        float *vec, float scalew, float scaleh)
{
    const int direction = s->out_cubemap_direction_order[face];
    float l_x, l_y, l_z;

    uf /= scalew;
    vf /= scaleh;

    rotate_cube_face_inverse(&uf, &vf, s->out_cubemap_face_rotation[face]);

    switch (direction) {
    case RIGHT:
        l_x =  1.f;
        l_y = -vf;
        l_z =  uf;
        break;
    case LEFT:
        l_x = -1.f;
        l_y = -vf;
        l_z = -uf;
        break;
    case UP:
        l_x =  uf;
        l_y =  1.f;
        l_z = -vf;
        break;
    case DOWN:
        l_x =  uf;
        l_y = -1.f;
        l_z =  vf;
        break;
    case FRONT:
        l_x =  uf;
        l_y = -vf;
        l_z = -1.f;
        break;
    case BACK:
        l_x = -uf;
        l_y = -vf;
        l_z =  1.f;
        break;
    default:
        av_assert0(0);
    }

    vec[0] = l_x;
    vec[1] = l_y;
    vec[2] = l_z;

    normalize_vector(vec);
}