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
typedef  int /*<<< orphan*/  GLuint ;
typedef  int /*<<< orphan*/  GLfloat ;

/* Variables and functions */
 int /*<<< orphan*/  gen_faces (int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  make_player (int /*<<< orphan*/ *,float,float,float,float,float) ; 
 int /*<<< orphan*/ * malloc_faces (int,int) ; 

GLuint gen_player_buffer(float x, float y, float z, float rx, float ry) {
    GLfloat *data = malloc_faces(10, 6);
    make_player(data, x, y, z, rx, ry);
    return gen_faces(10, 6, data);
}