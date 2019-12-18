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
 int /*<<< orphan*/  GL_ARRAY_BUFFER ; 
 int /*<<< orphan*/  GL_DYNAMIC_DRAW ; 
 int /*<<< orphan*/  GL_ELEMENT_ARRAY_BUFFER ; 
 int /*<<< orphan*/  GL_FALSE ; 
 int /*<<< orphan*/  GL_FLOAT ; 
 int /*<<< orphan*/  GL_STATIC_DRAW ; 
 int MAP_NUM_LINES ; 
 int MAP_NUM_TOTAL_VERTICES ; 
 int /*<<< orphan*/  glBindBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBindVertexArray (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBufferData (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glEnableVertexAttribArray (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glGenBuffers (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glGenVertexArrays (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glGetAttribLocation (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  glVertexAttribPointer (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * map_line_indices ; 
 int /*<<< orphan*/ ** map_vertices ; 
 int /*<<< orphan*/  mesh ; 
 int /*<<< orphan*/ * mesh_vbo ; 

__attribute__((used)) static void make_mesh(GLuint program)
{
    GLuint attrloc;

    glGenVertexArrays(1, &mesh);
    glGenBuffers(4, mesh_vbo);
    glBindVertexArray(mesh);
    /* Prepare the data for drawing through a buffer inidices */
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh_vbo[3]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)* MAP_NUM_LINES * 2, map_line_indices, GL_STATIC_DRAW);

    /* Prepare the attributes for rendering */
    attrloc = glGetAttribLocation(program, "x");
    glBindBuffer(GL_ARRAY_BUFFER, mesh_vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * MAP_NUM_TOTAL_VERTICES, &map_vertices[0][0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(attrloc);
    glVertexAttribPointer(attrloc, 1, GL_FLOAT, GL_FALSE, 0, 0);

    attrloc = glGetAttribLocation(program, "z");
    glBindBuffer(GL_ARRAY_BUFFER, mesh_vbo[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * MAP_NUM_TOTAL_VERTICES, &map_vertices[2][0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(attrloc);
    glVertexAttribPointer(attrloc, 1, GL_FLOAT, GL_FALSE, 0, 0);

    attrloc = glGetAttribLocation(program, "y");
    glBindBuffer(GL_ARRAY_BUFFER, mesh_vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * MAP_NUM_TOTAL_VERTICES, &map_vertices[1][0], GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(attrloc);
    glVertexAttribPointer(attrloc, 1, GL_FLOAT, GL_FALSE, 0, 0);
}