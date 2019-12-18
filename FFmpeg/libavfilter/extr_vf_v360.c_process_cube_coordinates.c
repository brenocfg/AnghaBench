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
struct TYPE_3__ {int* in_cubemap_face_order; int /*<<< orphan*/ * in_cubemap_face_rotation; } ;
typedef  TYPE_1__ V360Context ;

/* Variables and functions */
#define  BACK 133 
#define  DOWN 132 
#define  FRONT 131 
#define  LEFT 130 
#define  RIGHT 129 
#define  UP 128 
 int /*<<< orphan*/  av_assert0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rotate_cube_face (float*,float*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rotate_cube_face_inverse (float*,float*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void process_cube_coordinates(const V360Context *s,
                                     float uf, float vf, int direction,
                                     float *new_uf, float *new_vf, int *face)
{
    /*
     *  Cubemap orientation
     *
     *           width
     *         <------->
     *         +-------+
     *         |       |                              U
     *         | up    |                   h       ------->
     * +-------+-------+-------+-------+ ^ e      |
     * |       |       |       |       | | i    V |
     * | left  | front | right | back  | | g      |
     * +-------+-------+-------+-------+ v h      v
     *         |       |                   t
     *         | down  |
     *         +-------+
     */

    *face = s->in_cubemap_face_order[direction];
    rotate_cube_face_inverse(&uf, &vf, s->in_cubemap_face_rotation[*face]);

    if ((uf < -1.f || uf >= 1.f) && (vf < -1.f || vf >= 1.f)) {
        // There are no pixels to use in this case
        *new_uf = uf;
        *new_vf = vf;
    } else if (uf < -1.f) {
        uf += 2.f;
        switch (direction) {
        case RIGHT:
            direction = FRONT;
            *new_uf =  uf;
            *new_vf =  vf;
            break;
        case LEFT:
            direction = BACK;
            *new_uf =  uf;
            *new_vf =  vf;
            break;
        case UP:
            direction = LEFT;
            *new_uf =  vf;
            *new_vf = -uf;
            break;
        case DOWN:
            direction = LEFT;
            *new_uf = -vf;
            *new_vf =  uf;
            break;
        case FRONT:
            direction = LEFT;
            *new_uf =  uf;
            *new_vf =  vf;
            break;
        case BACK:
            direction = RIGHT;
            *new_uf =  uf;
            *new_vf =  vf;
            break;
        default:
            av_assert0(0);
        }
    } else if (uf >= 1.f) {
        uf -= 2.f;
        switch (direction) {
        case RIGHT:
            direction = BACK;
            *new_uf =  uf;
            *new_vf =  vf;
            break;
        case LEFT:
            direction = FRONT;
            *new_uf =  uf;
            *new_vf =  vf;
            break;
        case UP:
            direction = RIGHT;
            *new_uf = -vf;
            *new_vf =  uf;
            break;
        case DOWN:
            direction = RIGHT;
            *new_uf =  vf;
            *new_vf = -uf;
            break;
        case FRONT:
            direction = RIGHT;
            *new_uf =  uf;
            *new_vf =  vf;
            break;
        case BACK:
            direction = LEFT;
            *new_uf =  uf;
            *new_vf =  vf;
            break;
        default:
            av_assert0(0);
        }
    } else if (vf < -1.f) {
        vf += 2.f;
        switch (direction) {
        case RIGHT:
            direction = UP;
            *new_uf =  vf;
            *new_vf = -uf;
            break;
        case LEFT:
            direction = UP;
            *new_uf = -vf;
            *new_vf =  uf;
            break;
        case UP:
            direction = BACK;
            *new_uf = -uf;
            *new_vf = -vf;
            break;
        case DOWN:
            direction = FRONT;
            *new_uf =  uf;
            *new_vf =  vf;
            break;
        case FRONT:
            direction = UP;
            *new_uf =  uf;
            *new_vf =  vf;
            break;
        case BACK:
            direction = UP;
            *new_uf = -uf;
            *new_vf = -vf;
            break;
        default:
            av_assert0(0);
        }
    } else if (vf >= 1.f) {
        vf -= 2.f;
        switch (direction) {
        case RIGHT:
            direction = DOWN;
            *new_uf = -vf;
            *new_vf =  uf;
            break;
        case LEFT:
            direction = DOWN;
            *new_uf =  vf;
            *new_vf = -uf;
            break;
        case UP:
            direction = FRONT;
            *new_uf =  uf;
            *new_vf =  vf;
            break;
        case DOWN:
            direction = BACK;
            *new_uf = -uf;
            *new_vf = -vf;
            break;
        case FRONT:
            direction = DOWN;
            *new_uf =  uf;
            *new_vf =  vf;
            break;
        case BACK:
            direction = DOWN;
            *new_uf = -uf;
            *new_vf = -vf;
            break;
        default:
            av_assert0(0);
        }
    } else {
        // Inside cube face
        *new_uf = uf;
        *new_vf = vf;
    }

    *face = s->in_cubemap_face_order[direction];
    rotate_cube_face(new_uf, new_vf, s->in_cubemap_face_rotation[*face]);
}