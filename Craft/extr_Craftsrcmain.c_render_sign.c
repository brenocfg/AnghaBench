#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__* typing_buffer; int /*<<< orphan*/  render_radius; int /*<<< orphan*/  ortho; int /*<<< orphan*/  fov; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  typing; } ;
struct TYPE_11__ {int /*<<< orphan*/  extra1; int /*<<< orphan*/  sampler; int /*<<< orphan*/  matrix; int /*<<< orphan*/  program; } ;
struct TYPE_9__ {int /*<<< orphan*/  ry; int /*<<< orphan*/  rx; int /*<<< orphan*/  z; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_10__ {TYPE_1__ state; } ;
typedef  TYPE_1__ State ;
typedef  TYPE_2__ Player ;
typedef  int /*<<< orphan*/  GLuint ;
typedef  int /*<<< orphan*/  GLfloat ;
typedef  TYPE_3__ Attrib ;

/* Variables and functions */
 scalar_t__ CRAFT_KEY_SIGN ; 
 int /*<<< orphan*/  GL_FALSE ; 
 int MAX_SIGN_LENGTH ; 
 int _gen_sign_buffer (int /*<<< orphan*/ *,int,int,int,int,char*) ; 
 int /*<<< orphan*/  del_buffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  draw_sign (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 TYPE_7__* g ; 
 int /*<<< orphan*/  gen_faces (int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glUniform1i (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  glUniformMatrix4fv (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,float*) ; 
 int /*<<< orphan*/  glUseProgram (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hit_test_face (TYPE_2__*,int*,int*,int*,int*) ; 
 int /*<<< orphan*/ * malloc_faces (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_matrix_3d (float*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,scalar_t__*,int) ; 

void render_sign(Attrib *attrib, Player *player) {
    if (!g->typing || g->typing_buffer[0] != CRAFT_KEY_SIGN) {
        return;
    }
    int x, y, z, face;
    if (!hit_test_face(player, &x, &y, &z, &face)) {
        return;
    }
    State *s = &player->state;
    float matrix[16];
    set_matrix_3d(
        matrix, g->width, g->height,
        s->x, s->y, s->z, s->rx, s->ry, g->fov, g->ortho, g->render_radius);
    glUseProgram(attrib->program);
    glUniformMatrix4fv(attrib->matrix, 1, GL_FALSE, matrix);
    glUniform1i(attrib->sampler, 3);
    glUniform1i(attrib->extra1, 1);
    char text[MAX_SIGN_LENGTH];
    strncpy(text, g->typing_buffer + 1, MAX_SIGN_LENGTH);
    text[MAX_SIGN_LENGTH - 1] = '\0';
    GLfloat *data = malloc_faces(5, strlen(text));
    int length = _gen_sign_buffer(data, x, y, z, face, text);
    GLuint buffer = gen_faces(5, length, data);
    draw_sign(attrib, buffer, length);
    del_buffer(buffer);
}